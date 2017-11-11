#include <gateSession.h>
#include <Util.h>
#include <world.h>

gateSession::gateSession(khaki::EventLoop* loop, std::string& host, uint16_t port, int timeout) :
        loop_(loop), conn_(new khaki::Connector(loop_, host, port, timeout)) {
    conn_->setConnectCallback(std::bind(&gateSession::OnConnected, this, std::placeholders::_1));
    conn_->setCloseCallback(std::bind(&gateSession::OnConnectClose, this, std::placeholders::_1));
    conn_->setReadCallback(std::bind(&gateSession::OnMessage, this, std::placeholders::_1));
    RegisterCmd();
}
gateSession::~gateSession() {
    log4cppDebug(khaki::logger, "gateSession::~gateSession");
    conn_.reset();
}

bool gateSession::ConnectGateway() {
    return conn_->connectServer();
}

void gateSession::Heartbeat() {
    gs::S2G_Ping msg;
    msg.set_now_time(khaki::util::getTime());
    std::string str = msg.SerializeAsString();
    
    SendPacket(uint32(gs::ProtoID::ID_S2G_Ping), 0, 0, str);
}

void gateSession::OnConnected(const khaki::TcpConnectorPtr& con) {
    gs::S2G_RegisterServer msg;
    msg.set_sid(1);

    std::string str = msg.SerializeAsString();
    SendPacket(uint32(gs::ProtoID::ID_S2G_RegisterServer), 0, 0, str);
    loop_->getTimer()->AddTimer(std::bind(&gateSession::Heartbeat, this), 1, 20);/*20s tick*/
}

void gateSession::OnMessage(const khaki::TcpConnectorPtr& con) {
    khaki::Buffer& buf = con->getReadBuf();
    while( buf.size() > 0 ) {
        if (!checkBufValid(buf)) break;
        struct PACKET pkt = Decode(buf.begin());
        buf.addBegin(pkt.len);
        DispatcherCmd(pkt);
    }
}

void gateSession::OnConnectClose(const khaki::TcpConnectorPtr& con) {
    log4cppDebug(khaki::logger, "OnConnectClose");
}

void gateSession::RegisterCmd() {
    command_[gs::ProtoID::ID_G2S_RegisterServer] = std::bind(&gateSession::HandlerRegisterSid, this, std::placeholders::_1);
    ///////////////////////////
}

void gateSession::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else {
        HandlerDirtyPacket(msg);
        //log4cppDebug(khaki::logger, "error proto : %d", msg.cmd);
    }
}

void gateSession::SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg) {
    struct PACKET pkt;
    pkt.len = PACKET_HEAD_LEN + msg.size();
    pkt.cmd = cmd;
    pkt.uid = uid;
    pkt.sid = sid;
    pkt.msg = msg;
    SendPacket(pkt);
}

void gateSession::SendPacket(struct PACKET& pkt) {
    std::string msg = Encode(pkt);
    conn_->send(msg.data(), msg.size());
}

bool gateSession::HandlerRegisterSid(struct PACKET& str) {
    log4cppDebug(khaki::logger, "gateway, HandlerRegisterSid Success %d", str.cmd);
    return false;
}

bool gateSession::HandlerDirtyPacket(struct PACKET& str) {
    gWorld.PushGateMsg(str);
    //log4cppDebug(khaki::logger, "gateSession::HandlerDirtyPacket queue size : %d", gWorld.getMsgSize());
    return true;
}