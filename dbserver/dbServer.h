#ifndef GAME_CLIENT_SERVER_H
#define GAME_CLIENT_SERVER_H
#include <khaki.h>
#include <Queue.h>
#include <unordered_map>
#include <gameSession.h>
#include <base/common.h>
#include <Mysql/dbsql.h>

#include <map>
#include <functional>

class dbServer {
public: 
    dbServer(khaki::EventLoop* loop, DbSQL* dbMysql, std::string host, int port, int threadNum);
    ~dbServer();

    void start();

    void OnConnection(const khaki::TcpClientPtr& con);
	void OnConnClose(const khaki::TcpClientPtr& con);
    gameSessionPtr GetGameSessionBySid(uint32 sid);
    void AddAuthGameSession(uint32 sid, uint32 sockFd);
    void RemoveAuthGameSession(uint32 sid);

    DbSQL* GetDb() { return dbMysql_; }
private:
    DbSQL* dbMysql_;
    khaki::TcpThreadServer server_;
	std::mutex mtx_;
	std::unordered_map<uint32/*sid*/, gameSessionPtr> sessionLists_;
    std::mutex authmtx_;
    std::map<uint32/*sid*/, uint32/*fd*/> authList_;
    khaki::queue<struct PACKET> queue_;
};

#endif