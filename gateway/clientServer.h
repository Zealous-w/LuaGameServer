#ifndef GAME_CLIENT_SERVER_H
#define GAME_CLIENT_SERVER_H
#include <khaki.h>
#include <Queue.h>
#include <unordered_map>
#include <clientSession.h>
#include <base/common.h>

#include <map>
#include <functional>

class clientServer {
public: 
    clientServer(khaki::EventLoop* loop, std::string host, int port, int threadNum);
    ~clientServer();

    void start();

    void OnConnection(const khaki::TcpClientPtr& con);
	void OnConnClose(const khaki::TcpClientPtr& con);
    clientSessionPtr GetClientSessionByUniqueId(uint64 uniqueId);
    void ShowOnlineNumber();
private:
    uint64 markId_;
    khaki::TcpThreadServer server_;
	std::mutex mtx_;
	std::unordered_map<uint64/*uniqueId*/, clientSessionPtr> sessionLists_;
    khaki::queue<struct PACKET> queue_;
};

#endif