#include <iostream>
#include <gameSession.h>
#include <gameServer.h>
#include <global.h>
#include <tinyxml.h>

int main(int argc, char* argv[]) {
    khaki::EventLoop loop;
	khaki::InitLog(khaki::logger, "./gateway.log", log4cpp::Priority::DEBUG);
	std::string filename = "../../gateway/gateway.xml";

	TiXmlDocument config;
	TiXmlElement* childElement = NULL;
    if ( !config.LoadFile(filename.c_str()) ) {
        log4cppDebug(khaki::logger, "Load config xml error");
        return 0;
	}

	TiXmlElement* root = config.RootElement();
	TiXmlElement* clientElement = root->FirstChildElement("client");
	childElement = clientElement->FirstChildElement("listen_host");
	std::string cHost = childElement->GetText();
	childElement = clientElement->FirstChildElement("listen_port");
	std::string cPort = childElement->GetText();

	TiXmlElement* gameElement = root->FirstChildElement("gameserver");
	childElement = gameElement->FirstChildElement("listen_host");
	std::string gHost = childElement->GetText();
	childElement = gameElement->FirstChildElement("listen_port");
	std::string gPort = childElement->GetText();

	g_cServer = new clientServer(&loop, cHost.c_str(), atoi(cPort.c_str()), std::thread::hardware_concurrency());
	g_gServer = new gameServer(&loop, gHost.c_str(), atoi(gPort.c_str()), std::thread::hardware_concurrency());
	
	g_cServer->start();
	g_gServer->start();

	loop.loop();
	//////
    delete g_cServer;
	delete g_gServer;
	log4cpp::Category::shutdown();
	google::protobuf::ShutdownProtobufLibrary();
    return 0;
}