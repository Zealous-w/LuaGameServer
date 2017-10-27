#include "mysqlHandler.h"
#include <Util.h>
#include <Log.h>
#include <protocol/in/base.pb.h>

MySQLHandler::MySQLHandler(std::string host, uint16_t port, std::string dbName, std::string user, std::string pwd):
        host_(host),port_(port),dbName_(dbName),user_(user),pwd_(pwd), db_(false),query_(db_.query()) {
}

MySQLHandler::~MySQLHandler() {

}

bool MySQLHandler::ConnectionDatabase() {
    bool ret = db_.connect(dbName_.c_str(), host_.c_str(), user_.c_str(), pwd_.c_str(), port_);
    if (ret == false) {
        log4cppDebug(khaki::logger, "mysql connect failed, h:%s, p:%d, db:%s", host_.c_str(), port_, dbName_.c_str());
        return false;
    }
    
    if (!CreateGameTable()) {
        return false;
    }
    return true;
}

bool MySQLHandler::CreateDbDatabase(std::string& dbName) {
    std::string sql = khaki::util::string_format("create dababase %s", dbName.c_str());
    bool ret = query_.exec(sql.c_str());
    if (ret) {
        return true;
    } else {
        log4cppDebug(khaki::logger, "CreateDbDatabase, query failed, %s", sql.c_str());
        return false;
    }
}

bool MySQLHandler::CreateDbTable(std::string& dbTable) {
    bool ret = query_.exec(dbTable.c_str());
    if (ret) {
        return true;
    } else {
        log4cppDebug(khaki::logger, "CreateDbTable, query failed, %s", query_.error());
        return false;
    }
}

mysqlpp::StoreQueryResult MySQLHandler::GetData(std::string& sql) {
    mysqlpp::StoreQueryResult ret;
    ret = query_.store();
    if (ret) {
        
    } else {
        log4cppDebug(khaki::logger, "query failed, %s", sql.c_str());
    }
    return ret;
}

void MySQLHandler::CloseMysql() {

}

bool MySQLHandler::GetUserBaseInfo(base::User* user, uint64 uid) {
    std::string sql = khaki::util::string_format("select * from user where userId=%d", uid);
    mysqlpp::StoreQueryResult ret = query_.store(sql.c_str());
    if (ret && ret.size()) {
        for (auto iter = ret.begin(); iter != ret.end(); ++iter) {
            mysqlpp::Row row = *iter;
            user->set_uid(row["userId"]);
            user->set_sid(row["sid"]);
            user->set_name(row["name"]);
            user->set_level(row["level"]);
            user->set_money(row["money"]);
        }
        return true;
    }
    //log4cppDebug(khaki::logger, "GetUserBaseInfo, query failed, retsize:%d", ret.size());
    return false;
}

bool MySQLHandler::NewUserBaseInfo(base::User& user) {
    std::string sql = khaki::util::string_format("insert into user(userId, name, level, sid, money) values(%d, '%s', %d, %d, %d)", 
                user.uid(), user.name().c_str(), user.level(), user.sid(), user.money());

    bool ret = query_.exec(sql.c_str());
    if (!ret) {
        log4cppDebug(khaki::logger, "NewUserBaseInfo, insert failed, %s",  query_.error());
        return false;
    }
    return true;
}

bool MySQLHandler::SaveUserBaseInfo(base::User& user) {
    std::string sql = khaki::util::string_format("update user set name='%s', level=%d, sid=%d, money=%d where userId=%d", 
                user.name().c_str(), user.level(), user.sid(), user.money(), user.uid());
    bool ret = query_.exec(sql.c_str());
    if (!ret) {
        log4cppDebug(khaki::logger, "SaveUserBaseInfo, update failed, %s",  query_.error());
        return false;
    }
    return true;
}

bool MySQLHandler::CreateGameTable() {
    std::string user = "CREATE TABLE IF NOT EXISTS user ("
        "userId  BIGINT UNSIGNED NOT NULL PRIMARY KEY,"
        "name VARCHAR(2048) NOT NULL,"
        "level INT UNSIGNED NOT NULL DEFAULT 0,"
        "sid INT UNSIGNED NOT NULL DEFAULT 0,"
        "money BIGINT UNSIGNED NOT NULL DEFAULT 0"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8";
    if (!CreateDbTable(user)) {
        log4cppError(khaki::logger, "create table user error");
        return false;
    }
    return true;
}

bool MySQLHandler::LoadUser(base::User* user, uint64 uid) {
    if (!GetUserBaseInfo(user, uid)) {
        //log4cppError(khaki::logger, "LoadUser, load base user error %d", uid);
        return false;
    }
    return true;
}