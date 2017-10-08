#include <gameSession.h>
#include <clientSession.h>
#include <global.h>
#include <base/error.h>

gameSession::gameSession(gameServer* server, const khaki::TcpClientPtr& conn) :
        server_(server), conn_(conn) {
    conn_->setReadCallback(std::bind(&gameSession::OnMessage, 
                        this, std::placeholders::_1));
    RegisterCmd();
}
gameSession::~gameSession(){}

void gameSession::OnMessage(const khaki::TcpClientPtr& con) {
    khaki::Buffer& buf = con->getReadBuf();
    while( buf.size() > 0 ) {
        if (!checkBufValid(buf)) break;
        struct PACKET pkt = Decode(buf.begin());
        buf.addBegin(pkt.len);
        DispatcherCmd(pkt);
    }
}

void gameSession::SendToGameServer(std::string& msg) {
    conn_->send(msg.c_str(), msg.size());
}

void gameSession::SendToClient(std::string& msg) {

}

void gameSession::RegisterCmd() {
    command_[gs::ProtoID::ID_S2G_Ping] = std::bind(&gameSession::HandlerPing, this, std::placeholders::_1);
    command_[gs::ProtoID::ID_S2G_RegisterServer] = std::bind(&gameSession::HandlerRegisterSid, this, std::placeholders::_1);
    command_[gs::ProtoID::ID_S2G_Login] = std::bind(&gameSession::HandlerLogin, this, std::placeholders::_1);
    command_[gs::ProtoID::ID_S2G_Create] = std::bind(&gameSession::HandlerCreate, this, std::placeholders::_1);
}

void gameSession::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else {
        HandlerDirtyPacket(msg);
        //log4cppDebug(khaki::logger, "error proto : %d", msg.cmd);
    }
}

void gameSession::SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg) {
    struct PACKET pkt;
    pkt.len = PACKET_HEAD_LEN + msg.size();
    pkt.cmd = cmd;
    pkt.uid = uid;
    pkt.sid = sid;
    pkt.msg = msg;
    SendPacket(pkt);
}

struct PACKET gameSession::BuildPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg) {
    struct PACKET pkt;
    pkt.len = PACKET_HEAD_LEN + msg.size();
    pkt.cmd = cmd;
    pkt.uid = uid;
    pkt.sid = sid;
    pkt.msg = msg;
    return pkt;
}

void gameSession::SendPacket(struct PACKET& pkt) {
    std::string msg = Encode(pkt);
    conn_->send(msg.c_str(), msg.size());
}

void gameSession::AddClient(uint64 uid, uint64 uniqueId) 
{ 
    std::unique_lock<std::mutex> lck(mtx_);
    clientLists_.insert(std::make_pair(uid, uniqueId));
}

void gameSession::RemoveClient(uint64 uid) {
    std::unique_lock<std::mutex> lck(mtx_);
    clientLists_.erase(uid);
    //log4cppDebug(khaki::logger, "gameSession::RemoveClient sid:%d, onlineNum:%d", sid_, clientLists_.size());
}

bool gameSession::HandlerPing(struct PACKET& pkt) {
    gs::S2G_Ping recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    uint32 now_time = recv.now_time();
}

bool gameSession::HandlerRegisterSid(struct PACKET& pkt) {
    gs::S2G_RegisterServer recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    sid_ = recv.sid();
    g_gServer->AddAuthGameSession(sid_, conn_->getUniqueId());
    gs::G2S_RegisterServer msg;
    uint32 msgId = gs::ProtoID::ID_G2S_RegisterServer;
    msg.set_ret(ERROR_LOGIN_SUCCESS);
    msg.set_sid(sid_);
    std::string msgStr = msg.SerializeAsString();
    SendPacket(msgId, pkt.uid, sid_, msgStr);
    log4cppDebug(khaki::logger, "gateway HandlerRegisterSid : %d", pkt.cmd);
    return false;
}

bool gameSession::HandlerLogin(struct PACKET& pkt) {
    gs::S2G_Login recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    uint32 status = recv.ret();
    uint64 tokenId = recv.tokenid();

    cs::S2C_Login msg;
    uint32 msgId = uint32(cs::ProtoID::ID_S2C_Login);
    msg.set_ret(recv.ret());
    std::string msgStr = msg.SerializeAsString();

    struct PACKET msgPkt =  BuildPacket(msgId, pkt.uid, sid_, msgStr);

    clientSessionPtr csp = g_cServer->GetClientSessionByUniqueId(tokenId);
    if (csp) {
        csp->StatusChange(uint8(status));
        if (status == ERROR_LOGIN_SUCCESS) {
            AddClient(csp->GetUid(), tokenId);
        }
        csp->SendPacket(msgPkt);
    }
   
    log4cppDebug(khaki::logger, "gateway HandlerLogin : tokenId:%d, ret:%d", tokenId, recv.ret());
}

bool gameSession::HandlerCreate(struct PACKET& pkt) {
    gs::S2G_Create recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    
    uint64 tokenId = recv.tokenid();

    cs::S2C_Create msg;
    uint32 msgId = uint32(cs::ProtoID::ID_S2C_Create);
    msg.set_ret(recv.ret());
    msg.set_uid(pkt.uid);
    std::string msgStr = msg.SerializeAsString();

    struct PACKET msgPkt =  BuildPacket(msgId, pkt.uid, sid_, msgStr);

    clientSessionPtr csp = g_cServer->GetClientSessionByUniqueId(tokenId);
    if (csp) {
        csp->SendPacket(msgPkt);
    }
    //log4cppDebug(khaki::logger, "gateway HandlerCreate : tokenId:%d, ret:%d", tokenId, recv.ret());
}

bool gameSession::HandlerDirtyPacket(struct PACKET& pkt) {
    auto client = clientLists_.find(pkt.uid);
    if (client == clientLists_.end()) {
        log4cppDebug(khaki::logger, "gateway HandlerDirtyPacket ERROR");
        return false;
    }

    clientSessionPtr csp = g_cServer->GetClientSessionByUniqueId(client->second);
    if (csp) {
        csp->SendPacket(pkt);
    }
    //log4cppDebug(khaki::logger, "gateway HandlerDirtyPacket SUCCESS");
    return false;
}