#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <vector>
#include <base/basic.h>
#include <Log.h>
#include <memory>
extern "C"  
{  
    #include <lua.h> 
    #include <lualib.h>   
    #include <lauxlib.h>    
    #include <luaconf.h>   
}
extern lua_State* L;

//typedef int (*LUA_FUNCTION)();

class Entry {
public:
    Entry(int handler);
    ~Entry();
    int getHandler() { return handler_; }
    void SetExpiredTime(uint32 expired) { expiredTime = expired; }
    uint32 GetExpiredTime() { return expiredTime; }
    
    void SetInterval(uint32 interval) { iv = interval; }
    uint32 GetInterval() { return iv; }
private:
    int handler_;
    uint32 iv;
    uint32 expiredTime;
};

class Scheduler {
public:
    typedef std::shared_ptr<Entry> EntryPtr;
    Scheduler();
    ~Scheduler();

    uint64 genTimerId() { return autoTimerId++; }
    uint64 AddTimer(uint32 after, uint32 iv, int func);
    void RemoveTimer(uint64 timerId);
    void printLua();
    void update(uint32 now);
private:
    uint64 autoTimerId;
    std::map<uint64, EntryPtr> mScheduler_;
};