package.path="../../gameserver/system/?.lua;../../gameserver/system/?.so;" 
user = require "user"
util = require "util"
item  = require "itemSystem"
proto = require "proto"

util.printTable(proto)

function dispatcherCmd(player, pkt)
    if proto[pkt.cmd] then
        proto[pkt.cmd](player, pkt)
        log.logInfo(string.format("lua.dispatcherCmd SUCCESS, %d", pkt.cmd))
    else
        log.logInfo(string.format("lua.dispatcherCmd ERROR, %d", pkt.cmd))
    end
end
