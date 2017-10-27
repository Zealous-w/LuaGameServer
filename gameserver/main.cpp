#include <iostream>
#include <gateSession.h>
#include <dbSession.h>
#include <tinyxml.h>
#include <world.h>

#include "luaInterface.h"

lua_State* L;
extern int  tolua_luaFuncInterface_open (lua_State* tolua_S);

int main(int argc, char* argv[]) {
    khaki::InitLog(khaki::logger, "./gameserver.log", log4cpp::Priority::DEBUG);

    //////////////   
    L = luaL_newstate(); 
    luaL_openlibs(L);

    tolua_luaFuncInterface_open(L);
    //|| lua_pcall(L, 0,0,0))
    if(luaL_dofile(L, "../../gameserver/system/main.lua"))  {
        log4cppDebug(khaki::logger,"error %s\n", lua_tostring(L, -1));
        return -1;
    }
    //////////////
    std::string filename = "../../gameserver/config.xml";
    TiXmlDocument config;
    TiXmlElement* childElement = nullptr;
    if ( !config.LoadFile(filename.c_str()) ) {
        log4cppDebug(khaki::logger, "Load config xml error");
        return 0;
    }

    TiXmlElement* root = config.RootElement();
	TiXmlElement* gateElement = root->FirstChildElement("gate");
	childElement = gateElement->FirstChildElement("gate_host");
	std::string gHost = childElement->GetText();
	childElement = gateElement->FirstChildElement("gate_port");
    std::string gPort = childElement->GetText();
    
    TiXmlElement* dbElement = root->FirstChildElement("db");
	childElement = dbElement->FirstChildElement("db_host");
	std::string dHost = childElement->GetText();
	childElement = dbElement->FirstChildElement("db_port");
	std::string dPort = childElement->GetText();

    khaki::EventLoop loop;
    
    gateSession* gSession = new gateSession(&loop, gHost, uint16_t(atoi(gPort.c_str())));
    if ( !gSession->ConnectGateway() ) {
        log4cppDebug(khaki::logger, "connect gateway failed !!");
        return 0;
    }

    dbSession* dSession = new dbSession(&loop, dHost, uint16_t(atoi(dPort.c_str())));
    if ( !dSession->ConnectDB() ) {
        log4cppDebug(khaki::logger, "connect DB failed !!");
        return 0;
    } 

    gWorld.SetSession(gSession, dSession);
    gWorld.Start();
    loop.loop();
    ////////////////////
    log4cppDebug(khaki::logger, "MAIN LOOP EXIT");
    gWorld.Stop();
    delete gSession;
    delete dSession;
    log4cpp::Category::shutdown();
	google::protobuf::ShutdownProtobufLibrary();
    return 0;
}