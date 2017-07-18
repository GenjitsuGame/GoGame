#include<iostream>

#include "Go.h"

using namespace std;

Go::Go() {
    winScore = 1;
}

Go::~Go() {


}

void Go::createGoban(unsigned int size) {
    game.createGoban(size);
}

enumIntersection Go::getStone(unsigned int x, unsigned int y) const {
    return game.getStone(x, y);
}

unsigned int Go::getSize() const {
    return game.getSize();
}

unsigned int Go::getScore(char color) const {
    return (color == 'N' ? black.getScore() : white.getScore());
}

bool Go::isWinner(char color) const {
    return (getScore(color) >= getWinScore());
}

unsigned int Go::getWinScore() const {
    return winScore;
}

bool Go::setWinScore(unsigned int newwinscore) {
    if (newwinscore > 3 || newwinscore < 1)
        return false;
    else
        winScore = newwinscore;
    return true;
}

bool Go::setKomi(unsigned int komi) {
    if (komi >= getWinScore() || komi < 1)
        return false;
    else
        white.addScore(komi);
    return true;
}

Coordinates Go::conv(const string &coord) const {
    if (coord[0] == 'I') {
        Coordinates badcoord(getSize() + 1, getSize() + 1);
        return badcoord;
    }
    unsigned int x = (int) coord[0] - 65;
    if (x > 8)
        --x;
    unsigned int y = (int) coord[1] - 49;
    if (coord.size() > 2)
        y = (y + 1) * 10 + (int) coord[2] - 49;
    Coordinates newcoord(x, y);
    return newcoord;
}

bool Go::isInGoban(const string &coord) const {
    Coordinates tmp = conv(coord);
    return (tmp.getX() < getSize() && tmp.getY() < getSize());
}

enumIntersection Go::getPion(const string &coord) const {
    Coordinates tmp = conv(coord);
    return getStone(tmp.getX(), tmp.getY());
}

bool Go::connexeVide(unsigned int x, unsigned y) {
    // ON SORT SI C'EST EMPTY
    if (x >= 1 && game.getStone(x - 1, y) == EMPTY)
        return true;
    if (y >= 1 && game.getStone(x, y - 1) == EMPTY)
        return true;
    if (x + 1 < game.getSize() && game.getStone(x + 1, y) == EMPTY)
        return true;
    if (x + 1 < game.getSize() && game.getStone(x, y + 1) == EMPTY)
        return true;
    return false;

}

unsigned int Go::surround(unsigned int x, unsigned int y, const enumIntersection &color) {
    vector<Coordinates> dejaTeste;
    vector<Coordinates> aTeste;


    Coordinates courant(x, y);


    do {
        // On change de coord courante
        if (aTeste.size() != 0) {
            courant = aTeste.back();
            aTeste.pop_back();
        }

        // ON RENTRE LES PIONS CONNEXES DANS A TESTE

        // Il faut qu'il ne soit pas deja test�, ni dans la tab de Atest� et il faut qu'il soit de bonne color
        if (courant.getX() >= 1 && game.getStone(courant.getX() - 1, courant.getY()) == color &&
            !Coordinates(courant.getX() - 1, courant.getY()).isInTab(aTeste)
            && !Coordinates(courant.getX() - 1, courant.getY()).isInTab(dejaTeste)) {
            aTeste.push_back(Coordinates(courant.getX() - 1, courant.getY()));
        }

        if (courant.getY() >= 1 && game.getStone(courant.getX(), courant.getY() - 1) == color &&
            !Coordinates(Coordinates(courant.getX(), courant.getY() - 1)).isInTab(aTeste)
            && !Coordinates(Coordinates(courant.getX(), courant.getY() - 1)).isInTab(dejaTeste)) {
            aTeste.push_back(Coordinates(courant.getX(), courant.getY() - 1));
        }
        if (courant.getX() + 1 < game.getSize() && game.getStone(courant.getX() + 1, courant.getY()) == color &&
            !Coordinates(courant.getX() + 1, courant.getY()).isInTab(aTeste)
            && !Coordinates(courant.getX() + 1, courant.getY()).isInTab(dejaTeste)) {
            aTeste.push_back(Coordinates(courant.getX() + 1, courant.getY()));
        }
        if (courant.getY() + 1 < game.getSize() && game.getStone(courant.getX(), courant.getY() + 1) == color &&
            !Coordinates(courant.getX(), courant.getY() + 1).isInTab(aTeste)
            && !Coordinates(courant.getX(), courant.getY() + 1).isInTab(dejaTeste)) {
            aTeste.push_back(Coordinates(courant.getX(), courant.getY() + 1));
        }


        // Si on trouve une case vide, on quitte
        if (connexeVide(courant.getX(), courant.getY()))
            return 0;



        // On rentre la coord courante dans DEJA TEST�
        dejaTeste.push_back(Coordinates(courant.getX(), courant.getY()));
    } while (!aTeste.empty());



    // On supprrime les pions et on retourne le nombre de pions supprim�s
    unsigned int nbPionSup = dejaTeste.size();
    for (vector<Coordinates>::const_iterator it = dejaTeste.begin(); it != dejaTeste.end(); ++it)
        game.editStone(it->getX(), it->getY(), EMPTY);
    return nbPionSup;
}

unsigned int Go::checkChain(unsigned int x, unsigned y, char turn) {
    Intersection couleur(turn);
    unsigned int nbPionsSup = 0;

    if (x >= 1 && game.getStone(x - 1, y) == couleur.getStone()) {
        nbPionsSup += surround(x - 1, y, couleur.getStone());
    }
    if (y >= 1 && game.getStone(x, y - 1) == couleur.getStone()) {
        nbPionsSup += surround(x, y - 1, couleur.getStone());
    }

    if (x + 1 < game.getSize() && game.getStone(x + 1, y) == couleur.getStone()) {
        nbPionsSup += surround(x + 1, y, couleur.getStone());
    }
    if (y + 1 < game.getSize() && game.getStone(x, y + 1) == couleur.getStone()) {
        nbPionsSup += surround(x, y + 1, couleur.getStone());
    }
    return nbPionsSup;
}

bool Go::putStone(char couleur, const string &pos) {
    Coordinates tmp = conv(pos);

    if (tmp.getX() >= game.getSize() || (tmp.getY() >= game.getSize())
        || getStone(tmp.getX(), tmp.getY()) != EMPTY
        || surround(tmp.getX(), tmp.getY(), (enumIntersection) couleur) > 0)
        return false;

    game.editStone(tmp.getX(), tmp.getY(), couleur);
    unsigned int nbPoints = checkChain(tmp.getX(), tmp.getY(), couleur);

    if (couleur == 'N')
        black.addScore(nbPoints);
    else
        white.addScore(nbPoints);
    return true;
}

unsigned int Go::getMoveNbr() const {
    return movesList.size();
}

void Go::addMove(const string &joueur, const string &move) {
    string tmp(joueur);
    tmp.append(" ");
    tmp.append(move);
    movesList.push_back(tmp);
}

void Go::newMoveList() {
    if (!movesList.empty())
        movesList.clear();
}

string Go::getMove(unsigned int i) const {
    return movesList[i];
}
