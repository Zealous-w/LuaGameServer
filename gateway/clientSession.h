#ifndef GAME_CLIENT_SESSION_H
#define GAME_CLIENT_SESSION_H
#include <khaki.h>
#include <unordered_map>
#include <Queue.h>
#include <base/basic.h>
#include <base/common.h>
#include <protocol/out/cs.pb.h>
#include <protocol/in/gs.pb.h>
#include <protocol/in/base.pb.h>
#include <atomic>

class gameSession;
class clientServer;
class clientSession {
public:
    enum status {
        E_STATUS_NONE   = 0,
        E_STATUS_LOGIN  = 1,
        E_STATUS_CREATE = 2,
        E_STATUS_VALID  = 3,
        E_STATUS_LOGOUT = 4,
    };
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    clientSession(clientServer* server, const khaki::TcpClientPtr& conn);
    ~clientSession();

	void OnMessage(const khaki::TcpClientPtr& con);

    void RegisterCmd();
    void DispatcherCmd(struct PACKET& msg);
    void SendPacket(struct PACKET& pkt);
    void SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg);
    void SendToServer(struct PACKET& msg);
    void UnAuthSendToServer(struct PACKET& msg);
    uint8 GetStatus() { return status_.load(); }
    void SetStatus(uint8 status) { status_.store(status); }
    void StatusChange(uint8 status);
    void UserOffline();
    uint64 GetUid() { return uid_; }
    uint32 GetSid() { return sid_; }
    uint64 GetUniqueId() { return conn_->getUniqueId(); }
private:
    std::atomic<uint8_t> status_;
    uint64 uid_;
    uint32 sid_;
    std::map<uint32, ServiceFunc> command_;
    khaki::TcpClientPtr conn_;
    clientServer* server_;
    std::weak_ptr<gameSession> gameSession_;
    khaki::queue<struct PACKET> msgQueue_;
public:
    bool HandlerPing(struct PACKET& pkt);
    bool HandlerLogin(struct PACKET& pkt);
    bool HandlerCreate(struct PACKET& pkt);
    bool HandlerDirtyPacket(struct PACKET& str);
};

typedef std::shared_ptr<clientSession> clientSessionPtr;
#endif