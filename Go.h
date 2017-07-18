#ifndef GO_H_
#define GO_H_


#include <iostream>

#include "Player.h"
#include "Goban.h"
#include "Coordinates.h"

using namespace std;


class Go {
public:

    Go();

    ~Go();

    void createGoban(unsigned int size);

    enumIntersection getStone(unsigned int x, unsigned int y) const;

    unsigned int getSize() const;

    unsigned int getScore(char color) const;


    bool isWinner(char color) const;


    unsigned int getWinScore() const;

    bool setWinScore(unsigned int newwinscore);

    bool setKomi(unsigned int komi);

    Coordinates conv(const string &coord) const;

    bool isInGoban(const string &coord) const;

    enumIntersection getPion(const string &coord) const;

    bool connexeVide(unsigned int x, unsigned y);

    unsigned int surround(unsigned int x, unsigned int y, const enumIntersection &color);

    unsigned int checkChain(unsigned int x, unsigned y, char turn);

    bool putStone(char couleur, const string &pos);

    unsigned int getMoveNbr() const;

    void addMove(const string &joueur, const string &move);

    void newMoveList();

    string getMove(unsigned int i) const;

private:

    Goban game;
    Player black;
    Player white;
    unsigned int winScore;
    vector<string> movesList;
};


#endif /* GOBAN_H_ */
