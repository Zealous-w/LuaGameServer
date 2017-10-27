#include <clientSession.h>
#include <gameSession.h>
#include <global.h>
#include <base/error.h>

clientSession::clientSession(clientServer* server, const khaki::TcpClientPtr& conn):
    server_(server), conn_(conn), status_(0) {
    conn_->setReadCallback(std::bind(&clientSession::OnMessage, 
                        this, std::placeholders::_1));
    RegisterCmd();
}

clientSession::~clientSession() {

}

void clientSession::RegisterCmd() {
    command_[cs::ProtoID::ID_C2S_Ping] = std::bind(&clientSession::HandlerPing, this, std::placeholders::_1);
    command_[cs::ProtoID::ID_C2S_Login] = std::bind(&clientSession::HandlerLogin, this, std::placeholders::_1);
    command_[cs::ProtoID::ID_C2S_Create] = std::bind(&clientSession::HandlerCreate, this, std::placeholders::_1);
}

void clientSession::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else if (GetStatus() == E_STATUS_VALID) {
        SendToServer(msg);
    } else {
        log4cppDebug(khaki::logger, "clientSession error proto : %d, %d", msg.cmd, command_.size());
    }
}

void clientSession::OnMessage(const khaki::TcpClientPtr& con) {
    khaki::Buffer& buf = con->getReadBuf();
    while( buf.size() > 0 ) {
        if (!checkBufValid(buf)) break;
        struct PACKET pkt = Decode(buf.begin());
        buf.addBegin(pkt.len);
        DispatcherCmd(pkt);
    }
}   

void clientSession::SendPacket(struct PACKET& pkt) {
    std::string msg = Encode(pkt);
    conn_->send(msg.data(), msg.size());
}

void clientSession::SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg) {
    struct PACKET pkt;
    pkt.len = PACKET_HEAD_LEN + msg.size();
    pkt.cmd = cmd;
    pkt.uid = uid;
    pkt.sid = sid;
    pkt.msg = msg;
    SendPacket(pkt);
}

void clientSession::SendToServer(struct PACKET& msg) {
    std::shared_ptr<gameSession> gsp = gameSession_.lock();
    if ( gsp ) {
        std::string str = Encode(msg);
        gsp->SendToGameServer(str);
    } else {
        log4cppDebug(khaki::logger, "Auth, gameserver not exist error");
    }
}

void clientSession::UnAuthSendToServer(struct PACKET& msg) {
    std::shared_ptr<gameSession> gsp = g_gServer->GetGameSessionBySid(msg.sid);
    if ( gsp ) {
        std::string str = Encode(msg);
        gsp->SendToGameServer(str);
    } else {
         log4cppDebug(khaki::logger, "UnAuth, gameserver not exist");
    }
}

void clientSession::StatusChange(uint8 status) {
    if (status == ERROR_LOGIN_FAILED) {
        SetStatus(E_STATUS_NONE);
    } else if (status == ERROR_LOGIN_ROLE_NOT_FOUND) {
        SetStatus(E_STATUS_CREATE);
    } else if (status == ERROR_LOGIN_SUCCESS) {
        SetStatus(E_STATUS_VALID);
    }
}

void clientSession::UserOffline() {
    if (GetStatus() != E_STATUS_VALID) {
        log4cppDebug(khaki::logger, "UserOffline status : %d", GetStatus());
        return;
    }

    std::shared_ptr<gameSession> gsp = gameSession_.lock();
    if ( gsp ) {
        gsp->RemoveClient(uid_);
    }

    gs::G2S_LoginOffline msg;
    uint32 msgId = uint32(gs::ProtoID::ID_G2S_LoginOffline);
    msg.set_uid(uid_);
    std::string msgStr = msg.SerializeAsString();
    struct PACKET data;
    data.len = PACKET_HEAD_LEN + msgStr.size();
    data.cmd = msgId;
    data.sid = sid_;
    data.msg = msgStr;

    SendToServer(data);
}   

bool clientSession::HandlerPing(struct PACKET& pkt) {
    cs::C2S_Ping recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    //log4cppDebug(khaki::logger, "HandlerPing uid : %d, sid : %d, cmd : %d", pkt.uid, pkt.sid, pkt.cmd);
}

bool clientSession::HandlerLogin(struct PACKET& pkt) {
    cs::C2S_Login recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    gs::G2S_Login msg;
    uint32 msgId = uint32(gs::ProtoID::ID_G2S_Login);
    msg.set_tokenid(conn_->getUniqueId());
    msg.set_uid(recv.uid());
    uid_ = recv.uid();
    sid_ = pkt.sid;
    std::string msgStr = msg.SerializeAsString();
    struct PACKET data;
    data.len = PACKET_HEAD_LEN + msgStr.size();
    data.cmd = msgId;
    data.sid = pkt.sid;
    data.msg = msgStr;

    gameSession_ = g_gServer->GetGameSessionBySid(data.sid);
    SendToServer(data);
    //log4cppDebug(khaki::logger, "HandlerLogin uid : %d, sid : %d, cmd : %d", pkt.uid, pkt.sid, pkt.cmd);
}

bool clientSession::HandlerCreate(struct PACKET& pkt) {
    cs::C2S_Create recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    gs::G2S_Create msg;
    uint32 msgId = uint32(gs::ProtoID::ID_G2S_Create);
    msg.set_tokenid(conn_->getUniqueId());
    msg.set_uid(recv.uid());
    std::string msgStr = msg.SerializeAsString();
    struct PACKET data;
    data.len = PACKET_HEAD_LEN + msgStr.size();
    data.cmd = msgId;
    data.uid = pkt.uid;
    data.sid = pkt.sid;
    data.msg = msgStr;
    
    SendToServer(data);
    //log4cppDebug(khaki::logger, "HandlerCreate uid : %d, sid : %d, cmd : %d", pkt.uid, pkt.sid, pkt.cmd);
}

bool clientSession::HandlerDirtyPacket(struct PACKET& str) {

}