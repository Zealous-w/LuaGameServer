package.path="../../gameserver/system/?.lua;"  
item  = require "itemSystem"
proto = require "proto"

-- test
-- item.test()
-- proto[10022]()
log.logInfo("hello world")

function dispatcherCmd(player, pkt)
    if proto[pkt.cmd] then
        proto[pkt.cmd](player, pkt)
        log.logInfo(string.format("lua.dispatcherCmd SUCCESS, %d", pkt.cmd))
    else
        log.logInfo(string.format("lua.dispatcherCmd ERROR, %d", pkt.cmd))
    end
end
