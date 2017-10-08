#ifndef GAME_SESSION_H
#define GAME_SESSION_H
#include <khaki.h>
#include <Queue.h>
#include <map>

#include <base/basic.h>
#include <base/common.h>
#include <protocol/out/cs.pb.h>
#include <protocol/in/gs.pb.h>

class clientSession;
class gameServer;
class gameSession {
public:
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    gameSession(gameServer* server, const khaki::TcpClientPtr& conn);
    ~gameSession();

	void OnMessage(const khaki::TcpClientPtr& con);

    void RegisterCmd();
    void DispatcherCmd(struct PACKET& msg);

    void SendToGameServer(std::string& msg);

    void SendToClient(std::string& msg);
    void SendPacket(struct PACKET& pkt);
    void SendPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg);
    uint32 GetSid() { return sid_; }
    struct PACKET BuildPacket(uint32 cmd, uint64 uid, uint32 sid, std::string& msg);
    void AddClient(uint64 uid, uint64 uniqueId);
    void RemoveClient(uint64 uid);
private:
    uint32 sid_;
    khaki::TcpClientPtr conn_;
    gameServer* server_;
    std::map<uint32, ServiceFunc> command_;
    khaki::queue<struct PACKET> msgQueue_;
    std::mutex mtx_;
    std::map<uint64/*uid*/, uint64/*uniqueId*/> clientLists_;
public:
    bool HandlerPing(struct PACKET& pkt);
    bool HandlerRegisterSid(struct PACKET& pkt);
    bool HandlerLogin(struct PACKET& pkt);
    bool HandlerCreate(struct PACKET& pkt);
    bool HandlerDirtyPacket(struct PACKET& pkt);
};

typedef std::shared_ptr<gameSession> gameSessionPtr;
#endif