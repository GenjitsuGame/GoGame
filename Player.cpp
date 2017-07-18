#include "Player.h"

Player::Player() {
    score = 0;
}

unsigned int Player::getScore() const {
    return score;
}

void Player::addScore(unsigned int newscore) {
    score += newscore;
}
