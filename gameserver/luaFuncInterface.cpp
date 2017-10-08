/*
** Lua binding: luaFuncInterface
** Generated automatically by tolua++-1.0.92 on Sun Oct  8 04:28:46 2017.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_luaFuncInterface_open (lua_State* tolua_S);

#include"luaInterface.h"
#include <base/basic.h>
#include <base/common.h>
#include <protocol/in/base.pb.h>
#include "player.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_PACKET (lua_State* tolua_S)
{
 PACKET* self = (PACKET*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Player (lua_State* tolua_S)
{
 Player* self = (Player*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"uint64");
 tolua_usertype(tolua_S,"Player");
 tolua_usertype(tolua_S,"PACKET");
 tolua_usertype(tolua_S,"base::User");
 tolua_usertype(tolua_S,"uint32");
}

/* function: logInfo */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_log_logInfo00
static int tolua_luaFuncInterface_log_logInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   logInfo(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_PACKET_new00
static int tolua_luaFuncInterface_PACKET_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PACKET",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PACKET* tolua_ret = (PACKET*)  Mtolua_new((PACKET)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PACKET");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_PACKET_new00_local
static int tolua_luaFuncInterface_PACKET_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PACKET",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PACKET* tolua_ret = (PACKET*)  Mtolua_new((PACKET)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PACKET");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_len
static int tolua_get_PACKET_len(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->len,"uint32");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_len
static int tolua_set_PACKET_len(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint32",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->len = *((uint32*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cmd of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_cmd
static int tolua_get_PACKET_cmd(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cmd'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->cmd,"uint32");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cmd of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_cmd
static int tolua_set_PACKET_cmd(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cmd'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint32",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cmd = *((uint32*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_uid
static int tolua_get_PACKET_uid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->uid,"uint64");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_uid
static int tolua_set_PACKET_uid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint64",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uid = *((uint64*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_sid
static int tolua_get_PACKET_sid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->sid,"uint32");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_sid
static int tolua_set_PACKET_sid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint32",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sid = *((uint32*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: msg of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_msg
static int tolua_get_PACKET_msg(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'msg'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->msg);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: msg of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_msg
static int tolua_set_PACKET_msg(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'msg'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->msg = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_new00
static int tolua_luaFuncInterface_Player_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Player* tolua_ret = (Player*)  Mtolua_new((Player)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_new00_local
static int tolua_luaFuncInterface_Player_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Player* tolua_ret = (Player*)  Mtolua_new((Player)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Player");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_delete00
static int tolua_luaFuncInterface_Player_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveUser of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_SaveUser00
static int tolua_luaFuncInterface_Player_SaveUser00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveUser'", NULL);
#endif
  {
   base::User* tolua_ret = (base::User*)  self->SaveUser();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"base::User");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveUser'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uid of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_uid
static int tolua_get_Player_uid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->uid,"uint64");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uid of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_uid
static int tolua_set_Player_uid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint64",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uid = *((uint64*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sid of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_sid
static int tolua_get_Player_sid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->sid,"uint32");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sid of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_sid
static int tolua_set_Player_sid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint32",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sid = *((uint32*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_name
static int tolua_get_Player_name(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_name
static int tolua_set_Player_name(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_level
static int tolua_get_Player_level(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->level,"uint32");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_level
static int tolua_set_Player_level(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint32",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = *((uint32*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: money of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_money
static int tolua_get_Player_money(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'money'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->money,"uint64");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: money of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_money
static int tolua_set_Player_money(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'money'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint64",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->money = *((uint64*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_luaFuncInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"log",0);
  tolua_beginmodule(tolua_S,"log");
   tolua_function(tolua_S,"logInfo",tolua_luaFuncInterface_log_logInfo00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PACKET","PACKET","",tolua_collect_PACKET);
  #else
  tolua_cclass(tolua_S,"PACKET","PACKET","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PACKET");
   tolua_function(tolua_S,"new",tolua_luaFuncInterface_PACKET_new00);
   tolua_function(tolua_S,"new_local",tolua_luaFuncInterface_PACKET_new00_local);
   tolua_function(tolua_S,".call",tolua_luaFuncInterface_PACKET_new00_local);
   tolua_variable(tolua_S,"len",tolua_get_PACKET_len,tolua_set_PACKET_len);
   tolua_variable(tolua_S,"cmd",tolua_get_PACKET_cmd,tolua_set_PACKET_cmd);
   tolua_variable(tolua_S,"uid",tolua_get_PACKET_uid,tolua_set_PACKET_uid);
   tolua_variable(tolua_S,"sid",tolua_get_PACKET_sid,tolua_set_PACKET_sid);
   tolua_variable(tolua_S,"msg",tolua_get_PACKET_msg,tolua_set_PACKET_msg);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Player","Player","",tolua_collect_Player);
  #else
  tolua_cclass(tolua_S,"Player","Player","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Player");
   tolua_function(tolua_S,"new",tolua_luaFuncInterface_Player_new00);
   tolua_function(tolua_S,"new_local",tolua_luaFuncInterface_Player_new00_local);
   tolua_function(tolua_S,".call",tolua_luaFuncInterface_Player_new00_local);
   tolua_function(tolua_S,"delete",tolua_luaFuncInterface_Player_delete00);
   tolua_function(tolua_S,"SaveUser",tolua_luaFuncInterface_Player_SaveUser00);
   tolua_variable(tolua_S,"uid",tolua_get_Player_uid,tolua_set_Player_uid);
   tolua_variable(tolua_S,"sid",tolua_get_Player_sid,tolua_set_Player_sid);
   tolua_variable(tolua_S,"name",tolua_get_Player_name,tolua_set_Player_name);
   tolua_variable(tolua_S,"level",tolua_get_Player_level,tolua_set_Player_level);
   tolua_variable(tolua_S,"money",tolua_get_Player_money,tolua_set_Player_money);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_luaFuncInterface (lua_State* tolua_S) {
 return tolua_luaFuncInterface_open(tolua_S);
};
#endif

