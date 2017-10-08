#ifndef DB_SESSION_H
#define DB_SESSION_H
#include <khaki.h>
#include <Queue.h>

#include <base/basic.h>
#include <base/common.h>
#include <protocol/in/sr.pb.h>
#include <player.h>

class dbSession {
public:
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    dbSession(khaki::EventLoop* loop, std::string& host, uint16_t port);
    ~dbSession();

    bool ConnectDB();
    void Loop();

    void OnConnected(const khaki::TcpConnectorPtr& con);
	void OnMessage(const khaki::TcpConnectorPtr& con);
    void OnConnectClose(const khaki::TcpConnectorPtr& con);
    void Heartbeat();
    void RegisterCmd();
    void DispatcherCmd(struct PACKET& msg);

    void SendPacket(struct PACKET& pkt);
    void SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg);
private:
    uint32 sid_;
	std::mutex mtx_;
    khaki::EventLoop* loop_;
    khaki::TcpConnectorPtr conn_;
    std::map<uint32, ServiceFunc> command_;
public:
    bool HandlerRegisterSid(struct PACKET& str);
    bool HandlerDirtyPacket(struct PACKET& str);
};

#endif