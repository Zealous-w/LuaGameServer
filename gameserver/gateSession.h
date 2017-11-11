#ifndef GATE_SESSION_H
#define GATE_SESSION_H
#include <khaki.h>
#include <Queue.h>
#include <unordered_map>

#include <base/basic.h>
#include <base/common.h>
#include <protocol/out/cs.pb.h>
#include <protocol/in/gs.pb.h>
#include <player.h>

class gateSession {
public:
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    gateSession(khaki::EventLoop* loop, std::string& host, uint16_t port, int timeout);
    ~gateSession();

    bool ConnectGateway();

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