#include "player.h"

Player::Player()
{
    isactive = false;
}

Player::Player(int type)
{
    isactive = false;
    chesstype = type;
}

Player::~Player()
{
}

void Player::setActive(bool in)
{
    isactive = in;
}

bool Player::getActive()
{
    return isactive;
}

void Player::setChesstype(int type)
{
    chesstype = type;
}

int Player::getChesstype()
{
    return chesstype;
}
