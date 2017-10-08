#include <player.h>

Player::Player() {

}

Player::~Player() {

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