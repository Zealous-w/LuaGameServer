#ifndef WORLD_H
#define WORLD_H
#include <map>
#include <thread>
#include <condition_variable>
#include <base/basic.h>
#include <base/common.h>
#include <player.h>
#include <Queue.h>
#include <Timer.h>
#include <TimerQueue.h>

#include <gateSession.h>
#include <dbSession.h>
#include <scheduler.h>
#include <tolua++.h>
extern "C"  
{  
    #include <lua.h> 
    #include <lualib.h>   
    #include <lauxlib.h>    
    #include <luaconf.h>   
}
extern lua_State* L;
#define REGISTER_CMD_CALLBACK(cmdId, func) \
    command_[uint32(cmdId)]  = std::bind(&World::func, this, std::placeholders::_1)

#define LUA_HANDLER_CMD_DISPATCHER "HandlerDispatcherCmd"
#define LUA_HANDLER_TIMER          "HandlerTimer"

class World {
public:
    typedef std::function<bool(struct PACKET&)> ServiceFunc;
    typedef std::map<uint64, Player*>           MapUsers;
    static World& getInstance() {
        static World w;
        return w;
    }
private:
    World();
    ~World();

private:
    bool running_;
    std::thread thread_;
    std::mutex mtx_;
    std::condition_variable cond_;
    MapUsers users_;
    khaki::TimerManager timerM_;
    khaki::TimerQueue timerQueue_;
    Scheduler schedule_;
    gateSession* gSession_;
    dbSession* dSession_;
    std::map<uint32, ServiceFunc> command_;
    khaki::queue<struct PACKET> msgQueue_;
    khaki::queue<struct PACKET> dbMsgQueue_;
public:
    void Start() { std::unique_lock<std::mutex> lck(mtx_); running_ = true; cond_.notify_all();}
    void Stop() { running_ = false; }
    void SetSession(gateSession* gSession, dbSession* dSession) { gSession_ = gSession; dSession_ = dSession; }
    void Run();
    khaki::TimerManager& GetTimer() { return timerM_; }
    khaki::TimerQueue& GetTimerQueue() { return timerQueue_; }
    Scheduler& GetScheduler() { return schedule_; }
    uint32_t getMsgSize() { return msgQueue_.size(); }
    void PushGateMsg(struct PACKET& t) { msgQueue_.push(t); }
    void PushDbMsg(struct PACKET& t) { dbMsgQueue_.push(t); }
    void MsgProcess(khaki::queue<struct PACKET>& msg);
    void RegisterCmd();
    void DispatcherCmd(struct PACKET& msg);
    void AddPlayer(Player* player);
    void RemovePlayer(uint64 uid);
    Player* GetPlayer(uint64 uid);
    void ShowOnlineNumber();
    void SendToGateway(uint32 msgId, uint64 uid, uint32 sid, std::string& msg);
    void SendToDb(uint32 msgId, uint64 uid, uint32 sid, std::string& msg);

    void HandlerLuaTimer();
public:
    bool HandlerLogin(struct PACKET& pkt);
    bool HandlerCreate(struct PACKET& pkt);
    bool HandlerOffline(struct PACKET& pkt);

    bool HandlerGetMoney(struct PACKET& pkt);
    bool HandlerAddItem(struct PACKET& pkt);
public:
    ///////dbs -> gs
    bool HandlerRSLogin(struct PACKET& pkt);
    bool HandlerRSCreate(struct PACKET& pkt);
};

#define gWorld World::getInstance()

#endif