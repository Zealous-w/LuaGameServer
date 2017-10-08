#include <iostream>
#include <gameSession.h>
#include <gameServer.h>
#include <global.h>

int main(int argc, char* argv[]) {
    khaki::EventLoop loop;
	khaki::InitLog(khaki::logger, "./gateway.log", log4cpp::Priority::DEBUG);

	g_cServer = new clientServer(&loop, "127.0.0.1", 9527, 4);
	g_gServer = new gameServer(&loop, "127.0.0.1", 9528, 4);
	
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