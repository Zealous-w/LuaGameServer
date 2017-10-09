-- player
local user = {}
user.SaveTable = function (player)
    local p = {
        uid = player.uid,
        sid = player.sid,
        name = player.name,
        level = player.level,
        money = player.money
    }
    return p
end

return user