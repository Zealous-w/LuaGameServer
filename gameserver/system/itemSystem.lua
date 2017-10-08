local itemSystem = {}

itemSystem.test = function ()
    log.logInfo("itemSystem.test")
end

itemSystem.addItem = function (player, msg)
    log.logInfo("itemSystem.addItem")
end

itemSystem.removeItem = function (player, msg)
    log.logInfo("itemSystem.removeItem")
end

return itemSystem