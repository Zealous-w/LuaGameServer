#include <gameSession.h>
#include <dbServer.h>
#include <base/error.h>

gameSession::gameSession(dbServer* server, const khaki::TcpClientPtr& conn):
    server_(server), conn_(conn) {
    conn_->setReadCallback(std::bind(&gameSession::OnMessage, 
                        this, std::placeholders::_1));
    RegisterCmd();
}

gameSession::~gameSession() {

}

void gameSession::RegisterCmd() {
    REGISTER_GAME_CMD_CALLBACK(sr::ProtoID::ID_S2R_Ping, HandlerPing);
    REGISTER_GAME_CMD_CALLBACK(sr::ProtoID::ID_S2R_RegisterServer, HandlerRegisterSid);
    REGISTER_GAME_CMD_CALLBACK(sr::ProtoID::ID_S2R_Login, HandlerLogin);
    REGISTER_GAME_CMD_CALLBACK(sr::ProtoID::ID_S2R_Create, HandlerCreate);
    REGISTER_GAME_CMD_CALLBACK(sr::ProtoID::ID_S2R_SaveUser, HandlerSaveUser);
}

void gameSession::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else {
        log4cppDebug(khaki::logger, "error proto : %d", msg.cmd);
    }
}

void gameSession::OnMessage(const khaki::TcpClientPtr& con) {
    khaki::Buffer& buf = con->getReadBuf();
    while( buf.size() > 0 ) {
        if (!checkBufValid(buf)) break;
        struct PACKET pkt = Decode(buf.begin());
        buf.addBegin(pkt.len);
        DispatcherCmd(pkt);
    }
}

void gameSession::SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg) {
    struct PACKET pkt;
    pkt.len = PACKET_HEAD_LEN + msg.size();
    pkt.cmd = cmd;
    pkt.uid = uid;
    pkt.sid = sid_;
    pkt.msg = msg;
    SendPacket(pkt);
}

void gameSession::SendPacket(struct PACKET& pkt) {
    std::string msg = Encode(pkt);
    conn_->send(msg.c_str(), msg.size());
}

bool gameSession::HandlerPing(struct PACKET& pkt) {
    sr::S2R_Ping recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    //log4cppDebug(khaki::logger, "dbServer HandlerPing uid : %d, sid : %d, cmd : %d", pkt.uid, pkt.sid, pkt.cmd);
}

bool gameSession::HandlerRegisterSid(struct PACKET& str) {
    sr::S2R_RegisterServer recv;
    if ( !recv.ParseFromString(str.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", str.cmd);
        return false;
    }

    sid_ = recv.sid();
    server_->AddAuthGameSession(sid_, conn_->getFd());
    sr::R2S_RegisterServer msg;
    uint32 msgId = sr::ProtoID::ID_R2S_RegisterServer;
    msg.set_ret(ERROR_LOGIN_SUCCESS);
    msg.set_sid(sid_);
    std::string msgStr = msg.SerializeAsString();
    SendPacket(msgId, 0, 0, msgStr);
    log4cppDebug(khaki::logger, "dbServer HandlerRegisterSid, sid:%d cmd:%d", sid_, str.cmd);
    return false;
}

bool gameSession::HandlerLogin(struct PACKET& pkt) {
    sr::S2R_Login recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    uint64 uid = recv.uid();

    sr::R2S_Login msg;
    uint32 msgId = uint32(sr::ProtoID::ID_R2S_Login);
    base::User* user = msg.mutable_user();
    msg.set_ret(ERROR_LOGIN_SUCCESS);
    msg.set_tokenid(recv.tokenid());
    if (!server_->GetDb()->LoadUser(user, uid)) {
        msg.set_ret(ERROR_LOGIN_FAILED);
    }

    std::string msgStr = msg.SerializeAsString();
    SendPacket(msgId, pkt.uid, pkt.sid, msgStr);
    //log4cppDebug(khaki::logger, "dbMaster HandlerLogin uid : %d, sid : %d, cmd : %d", user->uid(), pkt.sid, pkt.cmd);
    return true;
}

bool gameSession::HandlerCreate(struct PACKET& pkt) {
    sr::S2R_Create recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    sr::R2S_Create msg;
    uint32 msgId = uint32(sr::ProtoID::ID_R2S_Create);
    msg.set_ret(ERROR_LOGIN_SUCCESS);
    msg.set_tokenid(recv.tokenid());
    base::User user = recv.user();
    if (!server_->GetDb()->NewUserBaseInfo(user)) {
        msg.set_ret(ERROR_LOGIN_FAILED);
    }

    std::string msgStr = msg.SerializeAsString();
    SendPacket(msgId, pkt.uid, pkt.sid, msgStr);
    //log4cppDebug(khaki::logger, "dbMaster HandlerLogin uid : %d, sid : %d, cmd : %d", pkt.uid, pkt.sid, pkt.cmd);
    return true;
}

bool gameSession::HandlerSaveUser(struct PACKET& pkt) {
    sr::S2R_SaveUser recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    base::User user = recv.user();
    server_->GetDb()->SaveUserBaseInfo(user);
    //log4cppDebug(khaki::logger, "dbMaster HandlerSaveUser uid : %d, sid : %d, cmd : %d", pkt.uid, pkt.sid, pkt.cmd);
    return true;
}