package.path="../../gameserver/system/?.lua;../../gameserver/system/?.so;" 
user = require "user"
util = require "util"
item  = require "itemSystem"
proto = require "proto"

-- util.printTable(proto)
--[[
function hello()
    log.logInfo(string.format("lua.timer Hello World"))
end
]]--
sceduler.AddTimer(1, 1, function() log.logInfo(string.format("lua.timer  Hello World  1s")) end)
sceduler.AddTimer(1, 5, function() log.logInfo(string.format("lua.timer  wang   5s")) end)
sceduler.AddTimer(1, 10, function() log.logInfo(string.format("lua.timer kai  10s")) end)
sceduler.AddTimer(1, 15, function() log.logInfo(string.format("lua.timer wei  15s")) end)
sceduler.AddTimer(1, 20, function() log.logInfo(string.format("lua.timer gan  20s")) end)
sceduler.AddTimer(1, 25, function() log.logInfo(string.format("lua.timer xie  25s")) end)
sceduler.AddTimer(1, 30, function() log.logInfo(string.format("lua.timer ni  30s")) end)

-- handler
function HandlerDispatcherCmd(player, pkt)
    if proto[pkt.cmd] then
        proto[pkt.cmd](player, pkt)
        log.logInfo(string.format("lua.dispatcherCmd SUCCESS, %d", pkt.cmd))
    else
        log.logInfo(string.format("lua.dispatcherCmd ERROR, %d", pkt.cmd))
    end
end