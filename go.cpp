#include<iostream>

#include "go.h"

using namespace std;

Go::Go() {
    winScore = 1;
}

Go::~Go() {


}

void Go::createGoban(unsigned int size) {
    jeu.createGoban(size);
}

enumIntersection Go::getPion(unsigned int x, unsigned int y) const {
    return jeu.getPion(x, y);
}

unsigned int Go::getTaille() const {
    return jeu.getTaille();
}

unsigned int Go::getScore(char couleur) const {
    return (couleur == 'N' ? noir.getScore() : blanc.getScore());
}

bool Go::isWinner(char couleur) const {
    return (getScore(couleur) >= getWinScore());
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
        blanc.addScore(komi);
    return true;
}

Coord Go::conv(const string &coord) const {
    if (coord[0] == 'I') {
        Coord badcoord(getTaille() + 1, getTaille() + 1);
        return badcoord;
    }
    unsigned int x = (int) coord[0] - 65;
    if (x > 8)
        --x;
    unsigned int y = (int) coord[1] - 49;
    if (coord.size() > 2)
        y = (y + 1) * 10 + (int) coord[2] - 49;
    Coord newcoord(x, y);
    return newcoord;
}

bool Go::estDansGoban(const string &coord) const {
    Coord tmp = conv(coord);
    return (tmp.getX() < getTaille() && tmp.getY() < getTaille());
}

enumIntersection Go::getPion(const string &coord) const {
    Coord tmp = conv(coord);
    return getPion(tmp.getX(), tmp.getY());
}

bool Go::connexeVide(unsigned int x, unsigned y) {
    // ON SORT SI C'EST VIDE
    if (x >= 1 && jeu.getPion(x - 1, y) == VIDE)
        return true;
    if (y >= 1 && jeu.getPion(x, y - 1) == VIDE)
        return true;
    if (x + 1 < jeu.getTaille() && jeu.getPion(x + 1, y) == VIDE)
        return true;
    if (x + 1 < jeu.getTaille() && jeu.getPion(x, y + 1) == VIDE)
        return true;
    return false;

}

unsigned int Go::entoure(unsigned int x, unsigned int y, const enumIntersection &couleur) {
    vector<Coord> dejaTeste;
    vector<Coord> aTeste;


    Coord courant(x, y);


    do {
        // On change de coord courante
        if (aTeste.size() != 0) {
            courant = aTeste.back();
            aTeste.pop_back();
        }

        // ON RENTRE LES PIONS CONNEXES DANS A TESTE

        // Il faut qu'il ne soit pas deja test�, ni dans la tab de Atest� et il faut qu'il soit de bonne couleur
        if (courant.getX() >= 1 && jeu.getPion(courant.getX() - 1, courant.getY()) == couleur &&
            !Coord(courant.getX() - 1, courant.getY()).presentDsTab(aTeste)
            && !Coord(courant.getX() - 1, courant.getY()).presentDsTab(dejaTeste)) {
            aTeste.push_back(Coord(courant.getX() - 1, courant.getY()));
        }

        if (courant.getY() >= 1 && jeu.getPion(courant.getX(), courant.getY() - 1) == couleur &&
            !Coord(Coord(courant.getX(), courant.getY() - 1)).presentDsTab(aTeste)
            && !Coord(Coord(courant.getX(), courant.getY() - 1)).presentDsTab(dejaTeste)) {
            aTeste.push_back(Coord(courant.getX(), courant.getY() - 1));
        }
        if (courant.getX() + 1 < jeu.getTaille() && jeu.getPion(courant.getX() + 1, courant.getY()) == couleur &&
            !Coord(courant.getX() + 1, courant.getY()).presentDsTab(aTeste)
            && !Coord(courant.getX() + 1, courant.getY()).presentDsTab(dejaTeste)) {
            aTeste.push_back(Coord(courant.getX() + 1, courant.getY()));
        }
        if (courant.getY() + 1 < jeu.getTaille() && jeu.getPion(courant.getX(), courant.getY() + 1) == couleur &&
            !Coord(courant.getX(), courant.getY() + 1).presentDsTab(aTeste)
            && !Coord(courant.getX(), courant.getY() + 1).presentDsTab(dejaTeste)) {
            aTeste.push_back(Coord(courant.getX(), courant.getY() + 1));
        }


        // Si on trouve une case vide, on quitte
        if (connexeVide(courant.getX(), courant.getY()))
            return 0;



        // On rentre la coord courante dans DEJA TEST�
        dejaTeste.push_back(Coord(courant.getX(), courant.getY()));
    } while (!aTeste.empty());



    // On supprrime les pions et on retourne le nombre de pions supprim�s
    unsigned int nbPionSup = dejaTeste.size();
    for (vector<Coord>::const_iterator it = dejaTeste.begin(); it != dejaTeste.end(); ++it)
        jeu.editPion(it->getX(), it->getY(), VIDE);
    return nbPionSup;
}

unsigned int Go::checkChaine(unsigned int x, unsigned y, char tour) {
    Intersection couleur(tour);
    unsigned int nbPionsSup = 0;

    if (x >= 1 && jeu.getPion(x - 1, y) == couleur.getPion()) {
        nbPionsSup += entoure(x - 1, y, couleur.getPion());
    }
    if (y >= 1 && jeu.getPion(x, y - 1) == couleur.getPion()) {
        nbPionsSup += entoure(x, y - 1, couleur.getPion());
    }

    if (x + 1 < jeu.getTaille() && jeu.getPion(x + 1, y) == couleur.getPion()) {
        nbPionsSup += entoure(x + 1, y, couleur.getPion());
    }
    if (y + 1 < jeu.getTaille() && jeu.getPion(x, y + 1) == couleur.getPion()) {
        nbPionsSup += entoure(x, y + 1, couleur.getPion());
    }
    return nbPionsSup;
}

bool Go::placerPion(char couleur, const string &pos) {
    Coord tmp = conv(pos);

    if (tmp.getX() >= jeu.getTaille() || (tmp.getY() >= jeu.getTaille())
        || getPion(tmp.getX(), tmp.getY()) != VIDE
        || entoure(tmp.getX(), tmp.getY(), (enumIntersection) couleur) > 0)
        return false;

    jeu.editPion(tmp.getX(), tmp.getY(), couleur);
    unsigned int nbPoints = checkChaine(tmp.getX(), tmp.getY(), couleur);

    if (couleur == 'N')
        noir.addScore(nbPoints);
    else
        blanc.addScore(nbPoints);
    return true;
}

unsigned int Go::getNbCoups() const {
    return listeCoup.size();
}

void Go::addCoup(const string &joueur, const string &coup) {
    string tmp(joueur);
    tmp.append(" ");
    tmp.append(coup);
    listeCoup.push_back(tmp);
}

void Go::newListeCoup() {
    if (!listeCoup.empty())
        listeCoup.clear();
}

string Go::getCoup(unsigned int i) const {
    return listeCoup[i];
}
