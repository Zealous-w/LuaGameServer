#include "luaInterface.h"
#include <Log.h>


void logInfo(const char* str) {
    log4cppInfo(khaki::logger, "%s", str);
}