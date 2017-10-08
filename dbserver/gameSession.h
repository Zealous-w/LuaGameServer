#ifndef GAME_SESSION_H
#define GAME_SESSION_H
#include <khaki.h>
#include <unordered_map>
#include <Queue.h>
#include <base/basic.h>
#include <base/common.h>
#include <protocol/in/sr.pb.h>

#define REGISTER_GAME_CMD_CALLBACK(cmdId, func) \
    command_[uint32(cmdId)]  = std::bind(&gameSession::func, this, std::placeholders::_1)


class dbServer;
class gameSession {
public:
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    gameSession(dbServer* server, const khaki::TcpClientPtr& conn);
    ~gameSession();

	void OnMessage(const khaki::TcpClientPtr& con);

    void RegisterCmd();
    void DispatcherCmd(struct PACKET& msg);

    void SendPacket(struct PACKET& pkt);
    void SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg);
    uint32 GetSid() { return sid_; }
private:
    uint8 status_;
    uint32 sid_;
    std::map<uint32, ServiceFunc> command_;
    khaki::TcpClientPtr conn_;
    dbServer* server_;
public:
    bool HandlerPing(struct PACKET& str);
    bool HandlerRegisterSid(struct PACKET& str);
    bool HandlerLogin(struct PACKET& pkt);
    bool HandlerCreate(struct PACKET& pkt);
    bool HandlerSaveUser(struct PACKET& pkt);
};

typedef std::shared_ptr<gameSession> gameSessionPtr;
#endif