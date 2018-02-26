#include "cliManager.h"
#include <Util.h>
#include <Log.h>
#include <unistd.h>
#include <sys/prctl.h>  
#include "callLua.h"

CliManager::CliManager() : mStatus_(true), thread_(&CliManager::Run, this){
    InitCommand();
    log4cppDebug(khaki::logger, "Console Thread Start");
}

CliManager::~CliManager() {
    thread_.join();
}

void CliManager::Start() {
    std::unique_lock<std::mutex> lck(mtx_); 
    mStatus_.store(true); 
    cond_.notify_all();
}

void CliManager::InitCommand() {
    mFunc_["reload"] = std::bind(&CliManager::reloadModule, this, std::placeholders::_1);
}

void CliManager::DispatcherCmd(const char* param) {
    std::vector<std::string> vParam;
    khaki::util::strSplit(std::string(param), " ", vParam);
    if(vParam.size()) {
        auto iter = mFunc_.find(vParam[0]);
        if (iter != mFunc_.end()) {
            std::string param;
            if (vParam.size() >= 2) param = vParam[1];
            iter->second(param);
        } else {
            log4cppError(khaki::logger, "ERROR NOT FOUND CMD: %s", vParam[0].c_str());
        }
    }
}

int kbHitReturn() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void CliManager::Run() {
    {
        std::unique_lock<std::mutex> lck(mtx_);
        cond_.wait(lck, [this]()->bool{ return mStatus_; });
    }
    ::prctl(PR_SET_NAME, "CliManager");
    
    log4cppDebug(khaki::logger, "Console Thread::Running");
    char commandbuf[256];
    while (mStatus_) {
        while (!kbHitReturn() && mStatus_.load())
            usleep(100);
        if (!mStatus_) break;

        char *command = fgets(commandbuf,sizeof(commandbuf),stdin);
        if (command != NULL) {
            for(int x=0;command[x];x++)
                if(command[x]=='\r'||command[x]=='\n')
            {
                command[x]=0;
                break;
            }
            DispatcherCmd(command);
        } else if (feof(stdin)) {
            mStatus_ = false;
        }
    }
}

//function
void CliManager::reloadModule(std::string& param) {
    log4cppDebug(khaki::logger, "Console reloadModule");
    
    int ret, value;
    ret = callLua("Reload", "", &value);
    if (ret != 0) {
        log4cppDebug(khaki::logger, "Console reloadModule Faild");
    }
}