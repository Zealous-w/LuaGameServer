#include <iostream>
#include <Log.h>
#include <base/basic.h>
#include <base/common.h>
#include <base/error.h>
#include <protocol/out/cs.pb.h>
#include <khaki.h>

class Client : public std::enable_shared_from_this<Client> {
public:
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    Client(khaki::EventLoop* loop, std::string host, uint16_t port, uint64 uid, uint32 sid, int timout) : 
        loop_(loop), conn_(new khaki::Connector(loop_, host, port, timout)), uid_(uid), sid_(sid){
        conn_->setConnectCallback(std::bind(&Client::OnConnected, this, 
                std::placeholders::_1));
        conn_->setCloseCallback(std::bind(&Client::OnConnectClose, this, 
                std::placeholders::_1));
        conn_->setReadCallback(std::bind(&Client::OnMessage, this, 
                std::placeholders::_1));
        RegisterCmd();

        ConnectGateway();
    }
    ~Client() {}

    bool ConnectGateway() {
        return conn_->connectServer();
    }

    void Loop() {
        loop_->loop();
    }
    void OnConnected(const khaki::TcpConnectorPtr& con) {
        cs::C2S_Login msg;
        msg.set_uid(uid_);
        log4cppDebug(khaki::logger, "OnConnected uid : %d", uid_);
        std::string str = msg.SerializeAsString();
        SendPacket(uint32(cs::ProtoID::ID_C2S_Login), str);
        ///start tick
        loop_->getTimer()->AddTimer(std::bind(&Client::Heartbeat, this), khaki::util::getTime(), 20);/*10s tick*/
    }
	void OnMessage(const khaki::TcpConnectorPtr& con) {
        khaki::Buffer& buf = con->getReadBuf();
        while( buf.size() > 0 ) {
            //if (!buf.checkInt32()) break;
            if (!checkBufValid(buf)) break;
            struct PACKET pkt = Decode(buf.begin());
            buf.addBegin(pkt.len);
            DispatcherCmd(pkt);
        }
    }
    void OnConnectClose(const khaki::TcpConnectorPtr& con) {

    }
    void Heartbeat() {
        cs::C2S_Ping msg;
        msg.set_now_time(khaki::util::getTime());
        std::string str = msg.SerializeAsString();
        
        SendPacket(uint32(cs::ProtoID::ID_C2S_Ping), str);
    }
    void RegisterCmd() {
        command_[cs::ProtoID::ID_S2C_Login] = std::bind(&Client::HandlerLogin, this, std::placeholders::_1);
        command_[cs::ProtoID::ID_S2C_Create] = std::bind(&Client::HandlerCreate, this, std::placeholders::_1);
        command_[cs::ProtoID::ID_S2C_GetMoney] = std::bind(&Client::HandlerGetMoney, this, std::placeholders::_1);
    }
    void DispatcherCmd(struct PACKET& msg) {
        if ( command_.find(msg.cmd) != command_.end() ) {
            command_[msg.cmd](msg);
        } else {
            log4cppDebug(khaki::logger, "error proto : %d", msg.cmd);
        }
    }
    void SendPacket(struct PACKET& pkt) {
        std::string msg = Encode(pkt);
        conn_->send(msg.c_str(), msg.size());
    }
    void SendPacket(uint32 cmd, std::string& msg) {
        struct PACKET pkt;
        pkt.len = PACKET_HEAD_LEN + msg.size();
        pkt.cmd = cmd;
        pkt.uid = uid_;
        pkt.sid = sid_;
        pkt.msg = msg;
        SendPacket(pkt);
    }

    void SetUid(uint32 uid) {
        uid_ = uid;
    }
    void SetSid(uint32 sid) {
        sid_ = sid;
    }
private:
    std::string host;
    uint16_t port;
    uint64 uid_;
    uint32 sid_;
    khaki::EventLoop* loop_;
    khaki::TcpConnectorPtr conn_;
    std::map<uint32, ServiceFunc> command_;

public:
    bool HandlerLogin(struct PACKET& msg) {
        cs::S2C_Login recv;
        if ( !recv.ParseFromString(msg.msg) )
        {
            log4cppDebug(khaki::logger, "proto parse error : %d", msg.cmd);
            return false;
        }

        uint32 ret = recv.ret();

        if (ret == ERROR_LOGIN_FAILED) {
            cs::C2S_Create msg2;
            msg2.set_uid(uid_);

            std::string str2 = msg2.SerializeAsString();
            SendPacket(uint32(cs::ProtoID::ID_C2S_Create), str2);
            log4cppDebug(khaki::logger, "Need Create Uid ret : %d", ret);
        }

        if (ret == ERROR_LOGIN_SUCCESS) {
            cs::C2S_GetMoney msg3;
            msg3.set_addmoney(500);

            std::string str3 = msg3.SerializeAsString();
            SendPacket(uint32(cs::ProtoID::ID_C2S_GetMoney), str3);
            log4cppDebug(khaki::logger, "I Need Money 500");
        }

        log4cppDebug(khaki::logger, "HandlerLogin ret : %d", ret);
        return true;
    }

    bool HandlerCreate(struct PACKET& msg) {
        cs::S2C_Create recv;
        if ( !recv.ParseFromString(msg.msg) )
        {
            log4cppDebug(khaki::logger, "proto parse error : %d", msg.cmd);
            return false;
        }

        uint32 ret = recv.ret();
        uint64 uid = recv.uid();

        if (ret == ERROR_LOGIN_SUCCESS) {
            cs::C2S_Login msg;
            msg.set_uid(uid_);
            log4cppDebug(khaki::logger, "HandlerCreate Login uid : %d", uid_);
            std::string str = msg.SerializeAsString();
            SendPacket(uint32(cs::ProtoID::ID_C2S_Login), str);
        }
        
        log4cppDebug(khaki::logger, "HandlerCreate ret : %d, uid : %d", ret, uid);
        return true;
    }

    bool HandlerGetMoney(struct PACKET& msg) {
        cs::S2C_GetMoney recv;
        if ( !recv.ParseFromString(msg.msg) )
        {
            log4cppDebug(khaki::logger, "proto parse error : %d", msg.cmd);
            return false;
        }

        uint32 ret = recv.ret();
        uint32 money = recv.summoney();
        log4cppDebug(khaki::logger, "HandlerGetMoney ret : %d, money : %d", ret, money);
        return true;
    }
};

int main(int argc, char* argv[]) {
    khaki::EventLoop loop;
    khaki::InitLog(khaki::logger, "./client.log", log4cpp::Priority::DEBUG);

    if (argc < 3) {
        log4cppDebug(khaki::logger, "Usage : ./client <sessionNumber> <uid>");
        return 0;
    }
    
    uint32 sessionNum = std::stoi(std::string(argv[1]));
    uint64 uidBegin = std::stoi(std::string(argv[2]));
    // Client* client = new Client(&loop, "127.0.0.1", 9527);
    // client->SetUid(123456);
    // client->SetSid(1);
    // if ( !client->ConnectGateway() ) {
    //     log4cppDebug(khaki::logger, "connect gateway failed !!");
    //     return 0;
    // }
    uint64 uid = uidBegin;
    std::vector<std::shared_ptr<Client>> vClients;
    for (int idx = 0; idx < sessionNum; idx++) {
        vClients.push_back(std::shared_ptr<Client>(new Client(&loop, "127.0.0.1", 9527, uid++, 1, 30)));
        //log4cppDebug(khaki::logger, "conn count : %d", idx);
    }

    loop.loop();

    ///////
    //delete client;
    log4cpp::Category::shutdown();
	google::protobuf::ShutdownProtobufLibrary();
    return 0;
}