#include "scheduler.h"
#include <Util.h>

Entry::Entry(int handler) {
    handler_ = handler;
}
Entry::~Entry() {
    luaL_unref(L, LUA_REGISTRYINDEX, this->handler_);
}

Scheduler::Scheduler() {

}

Scheduler::~Scheduler() {

}

uint64 Scheduler::AddTimer(uint32 after, uint32 iv, int func) {
    uint64 timerId = genTimerId();
    EntryPtr entry(new Entry(func));
    entry->SetExpiredTime(khaki::util::getTime() + after);
    entry->SetInterval(iv);
    mScheduler_.insert(std::make_pair(timerId, entry));
    return timerId;
}

void Scheduler::RemoveTimer(uint64 timerId) {
    auto iter = mScheduler_.find(timerId);
    if (iter == mScheduler_.end()) return;
    mScheduler_.erase(timerId);
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

void Scheduler::update(uint32 now) {
    for (auto iter = mScheduler_.begin(); iter != mScheduler_.end(); ++iter) {
        if (now >= iter->second->GetExpiredTime()) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, (*iter).second->getHandler());
            //printLua();
            if (lua_pcall(L, 0, 0, 0)) {
                log4cppDebug(khaki::logger, "lua_pcall error, %s", lua_tostring(L, -1));
                lua_pop(L, 1);
                continue;
            }

            uint32 iv = iter->second->GetInterval();
            if (iv != 0) {
                iter->second->SetExpiredTime(now + iv);
            } else {
                iter = mScheduler_.erase(iter);
                --iter;      
            }
        } 
    }
}