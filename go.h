#ifndef GO_H_
#define GO_H_


#include <iostream>

#include "joueur.h"
#include "goban.h"
#include "coord.h"

using namespace std;


class Go {
public:

    Go();

    ~Go();

    void createGoban(unsigned int size);

    enumIntersection getPion(unsigned int x, unsigned int y) const;

    unsigned int getTaille() const;

    unsigned int getScore(char couleur) const;


    bool isWinner(char couleur) const;


    unsigned int getWinScore() const;

    bool setWinScore(unsigned int newwinscore);

    bool setKomi(unsigned int komi);

    Coord conv(const string &coord) const;

    bool estDansGoban(const string &coord) const;

    enumIntersection getPion(const string &coord) const;

    bool connexeVide(unsigned int x, unsigned y);

    unsigned int entoure(unsigned int x, unsigned int y, const enumIntersection &couleur);

    unsigned int checkChaine(unsigned int x, unsigned y, char tour);

    bool placerPion(char couleur, const string &pos);

    unsigned int getNbCoups() const;

    void addCoup(const string &joueur, const string &coup);

    void newListeCoup();

    string getCoup(unsigned int i) const;

private:

    Goban jeu;
    Joueur noir;
    Joueur blanc;
    unsigned int winScore;
    vector<string> listeCoup;
};


#endif /* GOBAN_H_ */
