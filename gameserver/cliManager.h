#ifndef CMD_THREAD_H
#define CMD_THREAD_H 
#include <thread>
#include <map>
#include <atomic>
#include <thread>
#include <condition_variable>

class CliManager {
public:
    typedef std::function<void(std::string&)> CMDCallback;
    CliManager();
    ~CliManager();
    void Start();
    void Stop() { mStatus_.store(false); }
    void InitCommand();
    void DispatcherCmd(const char* param);
private:
    void Run();

    std::thread thread_;
    std::mutex mtx_;
    std::condition_variable cond_;
    std::map<std::string, CMDCallback> mFunc_;
    std::atomic<bool> mStatus_;
public:
    //function
    void reloadModule(std::string& param);
};

#endif