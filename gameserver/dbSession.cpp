#include <dbSession.h>
#include <Util.h>
#include <world.h>

dbSession::dbSession(khaki::EventLoop* loop, std::string& host, uint16_t port) :
        loop_(loop), conn_(new khaki::Connector(loop_, host, port)), sid_(0) {
    conn_->setConnectCallback(std::bind(&dbSession::OnConnected, this, std::placeholders::_1));
    conn_->setCloseCallback(std::bind(&dbSession::OnConnectClose, this, std::placeholders::_1));
    conn_->setReadCallback(std::bind(&dbSession::OnMessage, this, std::placeholders::_1));
    RegisterCmd();
}
dbSession::~dbSession(){}

bool dbSession::ConnectDB() {
    return conn_->connectServer();
}

void dbSession::Loop() {
    loop_->loop();
}

void dbSession::Heartbeat() {
    sr::S2R_Ping msg;
    msg.set_now_time(khaki::util::getTime());
    std::string str = msg.SerializeAsString();
    
    SendPacket(uint32(sr::ProtoID::ID_S2R_Ping), 0, sid_, str);
}

void dbSession::OnConnected(const khaki::TcpConnectorPtr& con) {
    sr::S2R_RegisterServer msg;
    msg.set_sid(1);

    std::string str = msg.SerializeAsString();
    SendPacket(uint32(sr::ProtoID::ID_S2R_RegisterServer), 0, sid_, str);
    loop_->getTimer()->AddTimer(std::bind(&dbSession::Heartbeat, this), khaki::util::getTime(), 10);/*10s tick*/
}

void dbSession::OnMessage(const khaki::TcpConnectorPtr& con) {
    khaki::Buffer& buf = con->getReadBuf();
    while( buf.size() > 0 ) {
        if (!checkBufValid(buf)) break;
        struct PACKET pkt = Decode(buf.begin());
        buf.addBegin(pkt.len);
        DispatcherCmd(pkt);
    }
}

void dbSession::OnConnectClose(const khaki::TcpConnectorPtr& con) {
    log4cppDebug(khaki::logger, "dbSession::OnConnectClose");
}

void dbSession::RegisterCmd() {
    command_[sr::ProtoID::ID_R2S_RegisterServer] = std::bind(&dbSession::HandlerRegisterSid, this, std::placeholders::_1);
    ///////////////////////////
}

void dbSession::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else {
        HandlerDirtyPacket(msg);
    }
}

void dbSession::SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg) {
    struct PACKET pkt;
    pkt.len = PACKET_HEAD_LEN + msg.size();
    pkt.cmd = cmd;
    pkt.uid = uid;
    pkt.sid = sid;
    pkt.msg = msg;
    SendPacket(pkt);
}

void dbSession::SendPacket(struct PACKET& pkt) {
    std::string msg = Encode(pkt);
    conn_->send(msg.c_str(), msg.size());
}

bool dbSession::HandlerRegisterSid(struct PACKET& str) {
    sr::R2S_RegisterServer recv;
    if ( !recv.ParseFromString(str.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", str.cmd);
        return false;
    }

    uint32 ret = recv.ret();
    sid_ = recv.sid();
    log4cppDebug(khaki::logger, "dbserver, HandlerRegisterSid Success %d %d %d", str.cmd, ret, sid_);
    return false;
}

bool dbSession::HandlerDirtyPacket(struct PACKET& str) {
    gWorld.PushDbMsg(str);
    return true;
}