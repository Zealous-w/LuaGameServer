local itemSystem = {}

itemSystem.addMoney = function (player, msg)
    recv = pb.decode("cs.C2S_GetMoney", msg.msg)
    print("recv.money = "..recv.addMoney)
    
    local csMsgId = protobuf.enum_id("cs.ProtoID", "ID_S2C_GetMoney")
    local csMsg = {
        ret = 1,
        sumMoney = 0,
    }

    addMoney = recv.addMoney
    
    if addMoney > 10000 then
        log.logInfo(string.format("Limit Money : %d, %d", player.uid, addMoney))
        csMsg.ret = 2
        csMsgBuffer = pb.encode("cs.S2C_GetMoney", csMsg)
        net.sendToGateway(csMsgId, player.uid, player.sid, csMsgBuffer)
        return
    end

    --
    player:SetMoney(player:GetMoney() + recv.addMoney)
    -- 

    --player cs
    csMsg.sumMoney = player:GetMoney();
    csMsgBuffer = pb.encode("cs.S2C_GetMoney", csMsg)
    net.SendToGateway(csMsgId, player.uid, player.sid, csMsgBuffer)

    --player:Save
    local msgId = protobuf.enum_id("sr.ProtoID", "ID_S2R_SaveUser")
    local userTable = user.SaveTable(player)
    --util.printTable(userTable)
    stringbuffer = pb.encode("sr.S2R_SaveUser", {
            user = userTable;
    })
    net.SendToDb(msgId, player.uid, player.sid, stringbuffer)
    log.logInfo(string.format("itemSystem.test, %d, %d [%d %d]", msg.cmd, msg.uid, player.level, player.money))
end

itemSystem.addItem = function (player, msg)
    log.logInfo("itemSystem.addItem")
end

itemSystem.removeItem = function (player, msg)
    log.logInfo("itemSystem.removeItem")
end

return itemSystem