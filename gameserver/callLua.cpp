#include <Log.h>
#include "callLua.h"
#include <stdarg.h>
#include <string.h>

extern "C" 
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

extern lua_State* L;

int callLua(const char* func, const char* sig, ...) {
    va_list vl;
    int narg, nres;
 
    va_start(vl, sig);
    lua_getglobal(L, func);
 
    narg = 0;
    while (*sig) {
		switch (*sig++) {
		case 'f': 
			lua_pushnumber(L, va_arg(vl, double));
			break;
		case 'd':
			lua_pushnumber(L, va_arg(vl, int));
            break;
        case 's': 
            lua_pushstring(L, va_arg(vl, char *));
            break;
        case '>':
            goto endwhile;
        default:
            {
                log4cppError(khaki::logger, "invalid option (%c)", *(sig - 1));
                return -1;
            }
        }
        narg++;
        luaL_checkstack(L, 1, "too many arguments");
    } endwhile:
 
    nres = strlen(sig);
    if (lua_pcall(L, narg, nres, 0) != 0) {
        log4cppError(khaki::logger, "error running function `%s': %s", func, lua_tostring(L, -1));
        return -1;
    }   
    
    nres = -nres;
    while (*sig) {
        switch (*sig++) {
 
        case 'f': 
            if (!lua_isnumber(L, nres)) {
                log4cppError(khaki::logger, "wrong result type");
                return -1;
            }
            *va_arg(vl, double *) = lua_tonumber(L, nres);
            break;
 
        case 'd': 
            if (!lua_isnumber(L, nres)) {
                log4cppError(khaki::logger, "wrong result type");
                return -1;
            }
              
           *va_arg(vl, int *) = (int)lua_tonumber(L, nres);
           break;
 
        case 's':
            if (!lua_isstring(L, nres)) {
                log4cppError(khaki::logger, "wrong result type");
                return -1;
            }   
           *va_arg(vl, const char **) = lua_tostring(L, nres);
           break;
 
       default:
           {
               log4cppError(khaki::logger, "invalid option (%c)", *(sig - 1));
               return -1;
           }
       }
       nres++;
    }
    va_end(vl);
    return 0;
}
