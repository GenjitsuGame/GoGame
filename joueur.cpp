#include "joueur.h"

Joueur::Joueur() {
    score = 0;
}

unsigned int Joueur::getScore() const {
    return score;
}

void Joueur::addScore(unsigned int newscore) {
    score += newscore;
}
