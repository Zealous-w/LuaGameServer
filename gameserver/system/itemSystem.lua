local itemSystem = {}

itemSystem.test = function (player, msg)
    player:SetLevel(654321)
    player:SetMoney(987)
    log.logInfo(string.format("itemSystem.test, %d, %d [%d %d]", msg.cmd, msg.uid, player.level, player.money))
end

itemSystem.addItem = function (player, msg)
    log.logInfo("itemSystem.addItem")
end

itemSystem.removeItem = function (player, msg)
    log.logInfo("itemSystem.removeItem")
end

return itemSystem