#include "scheduler.h"
#include <Util.h>

Scheduler::Scheduler():autoTimerId_(0) {

}

Scheduler::~Scheduler() {

}

uint32_t Scheduler::AddTimer(uint32_t after, uint32_t interval, int func) {
    uint32_t timerId = genTimerId();
    struct timeval tm, tm_iv;
    tm.tv_sec = khaki::util::getTime() + after;
    tm.tv_usec = 0;
    tm_iv.tv_sec = interval;
    tm_iv.tv_usec = 0;
    push(new Entry(timerId, tm, tm_iv, func));
    return timerId;
}

void Scheduler::RemoveTimer(uint32_t timerId) {
    for (int idx = 0; idx < size_; ++idx) {
        auto t = heap_[idx];
        if (t->timerId_ == timerId) {
            t->handler_ = -1;
            break;
        }
    }
}

void Scheduler::printLua() {
    int stackTop = lua_gettop(L);
    int nIdx = 0;  
    int nType;  
    
    log4cppDebug(khaki::logger, "top %d", stackTop);  

    for(nIdx = stackTop; nIdx > 0; --nIdx) {  
        nType = lua_type(L, nIdx);  
        log4cppDebug(khaki::logger, "%d, %s %s",nIdx, lua_typename(L,nType), lua_tostring(L,nIdx));  
    }  
}

void Scheduler::update(struct timeval& tm) {
    std::vector<Entry*> vAddEntry;
    while (!empty()) {
        auto t = front();
        if (timer_cmp(&t->tm_, &tm, <=)) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, t->getHandler());
            if (lua_pcall(L, 0, 0, 0)) {
                log4cppDebug(khaki::logger, "lua_pcall error, %s", lua_tostring(L, -1));
                lua_pop(L, 1);
                luaL_unref(L, LUA_REGISTRYINDEX, t->getHandler());
                pop();
                continue;
            }

            if (timer_set_interval((&t->interval_))) {
                timer_add(&tm, &t->interval_, &t->tm_);
                auto entry = new Entry(*t);
                entry->timerId_ = genTimerId();
                vAddEntry.push_back(entry);
            } else {
                luaL_unref(L, LUA_REGISTRYINDEX, t->getHandler());
            }

            pop();
        } else {
            break;
        }
    }

    for (auto iter : vAddEntry) {
        push(iter);
    }
}