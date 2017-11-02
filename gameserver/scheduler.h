#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <vector>
#include <base/basic.h>
#include <Log.h>
#include <memory>
#include <TimerQueue.h>
extern "C"  
{  
    #include <lua.h> 
    #include <lualib.h>   
    #include <lauxlib.h>    
    #include <luaconf.h>   
}
extern lua_State* L;

class Entry {
public:
    Entry(uint32_t timerId, struct timeval tm, struct timeval interval, int handler):
        timerId_(timerId), handler_(handler) {
        tm_.tv_sec = tm.tv_sec;
        tm_.tv_usec = tm.tv_usec;
        interval_.tv_sec = interval.tv_sec;
        interval_.tv_usec = interval.tv_usec;
    }

    Entry(Entry& timer) {
        tm_.tv_sec = timer.tm_.tv_sec;
        tm_.tv_usec = timer.tm_.tv_usec;
        interval_.tv_sec = timer.interval_.tv_sec;
        interval_.tv_usec = timer.interval_.tv_usec;
        handler_ = timer.handler_;
        timerId_ = timer.timerId_;
    }

    ~Entry() {}

    bool operator<(const Entry& timer) {
        return timer_cmp(&(this->tm_), &(timer.tm_), <);
    }

    int getHandler() { return handler_; }
public:
    int handler_;
    struct timeval tm_;
    struct timeval interval_;
    uint32_t timerId_;
};

class Scheduler : public khaki::MinHeap<Entry> {
public:
    Scheduler();
    ~Scheduler();

    uint32_t genTimerId() { return autoTimerId_++; }
    uint32_t AddTimer(uint32_t after, uint32_t interval, int func);
    void RemoveTimer(uint32_t timerId);

    void printLua();

    void update(struct timeval& tm);
private:
    uint32_t autoTimerId_;
};