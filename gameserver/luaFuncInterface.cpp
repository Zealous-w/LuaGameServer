/*
** Lua binding: luaFuncInterface
** Generated automatically by tolua++-1.0.92 on Mon Oct  9 03:25:48 2017.
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

/* function: sendToDb */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_net_sendToDb00
static int tolua_luaFuncInterface_net_sendToDb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"uint32",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint64",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"uint32",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  uint32 msgId = *((uint32*)  tolua_tousertype(tolua_S,1,0));
  uint64 uid = *((uint64*)  tolua_tousertype(tolua_S,2,0));
  uint32 sid = *((uint32*)  tolua_tousertype(tolua_S,3,0));
  std::string msg = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   sendToDb(msgId,uid,sid,msg);
   tolua_pushcppstring(tolua_S,(const char*)msg);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendToDb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SendToGateway */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_net_SendToGateway00
static int tolua_luaFuncInterface_net_SendToGateway00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"uint32",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint64",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"uint32",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  uint32 msgId = *((uint32*)  tolua_tousertype(tolua_S,1,0));
  uint64 uid = *((uint64*)  tolua_tousertype(tolua_S,2,0));
  uint32 sid = *((uint32*)  tolua_tousertype(tolua_S,3,0));
  std::string msg = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   SendToGateway(msgId,uid,sid,msg);
   tolua_pushcppstring(tolua_S,(const char*)msg);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendToGateway'.",&tolua_err);
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
#ifndef TOLUA_DISABLE_tolua_get_PACKET_unsigned_len
static int tolua_get_PACKET_unsigned_len(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->len);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_unsigned_len
static int tolua_set_PACKET_unsigned_len(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->len = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cmd of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_unsigned_cmd
static int tolua_get_PACKET_unsigned_cmd(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cmd'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->cmd);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cmd of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_unsigned_cmd
static int tolua_set_PACKET_unsigned_cmd(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cmd'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cmd = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_unsigned_uid
static int tolua_get_PACKET_unsigned_uid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->uid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_unsigned_uid
static int tolua_set_PACKET_unsigned_uid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uid = ((unsigned long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_get_PACKET_unsigned_sid
static int tolua_get_PACKET_unsigned_sid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sid of class  PACKET */
#ifndef TOLUA_DISABLE_tolua_set_PACKET_unsigned_sid
static int tolua_set_PACKET_unsigned_sid(lua_State* tolua_S)
{
  PACKET* self = (PACKET*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sid = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
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

/* method: Desc of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_Desc00
static int tolua_luaFuncInterface_Player_Desc00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Desc'", NULL);
#endif
  {
   self->Desc();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Desc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUid of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_GetUid00
static int tolua_luaFuncInterface_Player_GetUid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Player* self = (const Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUid'", NULL);
#endif
  {
   unsigned long long tolua_ret = (unsigned long long)  self->GetUid();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUid of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_SetUid00
static int tolua_luaFuncInterface_Player_SetUid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  unsigned long long tuid = ((unsigned long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUid'", NULL);
#endif
  {
   self->SetUid(tuid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_GetName00
static int tolua_luaFuncInterface_Player_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Player* self = (const Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_SetName00
static int tolua_luaFuncInterface_Player_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  std::string tname = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(tname);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSid of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_GetSid00
static int tolua_luaFuncInterface_Player_GetSid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Player* self = (const Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSid'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetSid();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSid of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_SetSid00
static int tolua_luaFuncInterface_Player_SetSid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tsid = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSid'", NULL);
#endif
  {
   self->SetSid(tsid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_GetLevel00
static int tolua_luaFuncInterface_Player_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Player* self = (const Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLevel of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_SetLevel00
static int tolua_luaFuncInterface_Player_SetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  unsigned int tlevel = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLevel'", NULL);
#endif
  {
   self->SetLevel(tlevel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMoney of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_GetMoney00
static int tolua_luaFuncInterface_Player_GetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Player* self = (const Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMoney'", NULL);
#endif
  {
   unsigned long long tolua_ret = (unsigned long long)  self->GetMoney();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMoney of class  Player */
#ifndef TOLUA_DISABLE_tolua_luaFuncInterface_Player_SetMoney00
static int tolua_luaFuncInterface_Player_SetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
  unsigned long long tmoney = ((unsigned long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMoney'", NULL);
#endif
  {
   self->SetMoney(tmoney);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uid of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_unsigned_uid
static int tolua_get_Player_unsigned_uid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->uid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uid of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_unsigned_uid
static int tolua_set_Player_unsigned_uid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uid = ((unsigned long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sid of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_unsigned_sid
static int tolua_get_Player_unsigned_sid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sid of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_unsigned_sid
static int tolua_set_Player_unsigned_sid(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sid = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
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
#ifndef TOLUA_DISABLE_tolua_get_Player_unsigned_level
static int tolua_get_Player_unsigned_level(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_unsigned_level
static int tolua_set_Player_unsigned_level(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: money of class  Player */
#ifndef TOLUA_DISABLE_tolua_get_Player_unsigned_money
static int tolua_get_Player_unsigned_money(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'money'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->money);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: money of class  Player */
#ifndef TOLUA_DISABLE_tolua_set_Player_unsigned_money
static int tolua_set_Player_unsigned_money(lua_State* tolua_S)
{
  Player* self = (Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'money'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->money = ((unsigned long long)  tolua_tonumber(tolua_S,2,0))
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
  tolua_module(tolua_S,"net",0);
  tolua_beginmodule(tolua_S,"net");
   tolua_function(tolua_S,"sendToDb",tolua_luaFuncInterface_net_sendToDb00);
   tolua_function(tolua_S,"SendToGateway",tolua_luaFuncInterface_net_SendToGateway00);
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
   tolua_variable(tolua_S,"len",tolua_get_PACKET_unsigned_len,tolua_set_PACKET_unsigned_len);
   tolua_variable(tolua_S,"cmd",tolua_get_PACKET_unsigned_cmd,tolua_set_PACKET_unsigned_cmd);
   tolua_variable(tolua_S,"uid",tolua_get_PACKET_unsigned_uid,tolua_set_PACKET_unsigned_uid);
   tolua_variable(tolua_S,"sid",tolua_get_PACKET_unsigned_sid,tolua_set_PACKET_unsigned_sid);
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
   tolua_function(tolua_S,"Desc",tolua_luaFuncInterface_Player_Desc00);
   tolua_function(tolua_S,"GetUid",tolua_luaFuncInterface_Player_GetUid00);
   tolua_function(tolua_S,"SetUid",tolua_luaFuncInterface_Player_SetUid00);
   tolua_function(tolua_S,"GetName",tolua_luaFuncInterface_Player_GetName00);
   tolua_function(tolua_S,"SetName",tolua_luaFuncInterface_Player_SetName00);
   tolua_function(tolua_S,"GetSid",tolua_luaFuncInterface_Player_GetSid00);
   tolua_function(tolua_S,"SetSid",tolua_luaFuncInterface_Player_SetSid00);
   tolua_function(tolua_S,"GetLevel",tolua_luaFuncInterface_Player_GetLevel00);
   tolua_function(tolua_S,"SetLevel",tolua_luaFuncInterface_Player_SetLevel00);
   tolua_function(tolua_S,"GetMoney",tolua_luaFuncInterface_Player_GetMoney00);
   tolua_function(tolua_S,"SetMoney",tolua_luaFuncInterface_Player_SetMoney00);
   tolua_variable(tolua_S,"uid",tolua_get_Player_unsigned_uid,tolua_set_Player_unsigned_uid);
   tolua_variable(tolua_S,"sid",tolua_get_Player_unsigned_sid,tolua_set_Player_unsigned_sid);
   tolua_variable(tolua_S,"name",tolua_get_Player_name,tolua_set_Player_name);
   tolua_variable(tolua_S,"level",tolua_get_Player_unsigned_level,tolua_set_Player_unsigned_level);
   tolua_variable(tolua_S,"money",tolua_get_Player_unsigned_money,tolua_set_Player_unsigned_money);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_luaFuncInterface (lua_State* tolua_S) {
 return tolua_luaFuncInterface_open(tolua_S);
};
#endif

