-- proto
pb = require "protobuf"
protobuf.register_file("../../server/protocol/out/cs.pb")
protobuf.register_file("../../server/protocol/in/base.pb")
protobuf.register_file("../../server/protocol/in/sr.pb")

local proto = {
    [protobuf.enum_id("cs.ProtoID", "ID_C2S_GetMoney")] = item.addMoney,
}

return proto