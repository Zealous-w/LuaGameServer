#include <player.h>
#include <Log.h>

Player::Player() {

}

Player::~Player() {

}

uint64_t Player::GetUid() const {
    return (uid);
}
void Player::SetUid(uint64_t tuid) {
    uid = tuid;
}
std::string Player::GetName() const {
    return name;
}
void Player::SetName(std::string tname) {
    name = tname;
}
uint32_t Player::GetSid() const {
    return sid;
}
void Player::SetSid(uint32_t tsid) {
    sid = tsid;
}
uint32_t Player::GetLevel() const {
    return level;
}
void Player::SetLevel(uint32_t tlevel) {
    level = tlevel;
}
uint64_t Player::GetMoney() const {
    return money;
}
void Player::SetMoney(uint64_t tmoney) {
    money = tmoney;
}

void Player::Desc() {
    log4cppDebug(khaki::logger, "Hello I'm Player");
}

base::User* Player::SaveUser() {
    base::User* u = new base::User();
    u->set_uid(uid);
    u->set_sid(sid);
    u->set_name(name);
    u->set_level(level);
    u->set_money(money);
    return u;
}