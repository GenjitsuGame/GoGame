#include<iostream>
#include <cstdlib>
#include <cstring>
#include <iostream>
// #include <boost/asio.hpp>
#include "Go.h"

// TODO : move server side...
using namespace std;
//using boost::asio::ip::tcp;

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
    unsigned int x = (unsigned int) coord[0] - 65;
    if (x > 8)
        --x;
    unsigned int y = (unsigned int) stoi(coord.substr(1, 2)) - 1;
    Coordinates newcoord(x, y);
    return newcoord;
}

bool Go::isInGoban(const string &coord) const {
    Coordinates tmp = conv(coord);
    return (tmp.getX() < getSize() && tmp.getY() < getSize());
}

enumIntersection Go::getStone(const string &coord) const {
    Coordinates tmp = conv(coord);
    return getStone(tmp.getX(), tmp.getY());
}

bool Go::connexeVide(unsigned int x, unsigned y) {
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
    vector<Coordinates> alreadyTested;
    vector<Coordinates> toTest;


    Coordinates current(x, y);


    do {
        if (toTest.size() != 0) {
            current = toTest.back();
            toTest.pop_back();
        }

        if (current.getX() >= 1 && game.getStone(current.getX() - 1, current.getY()) == color &&
            !Coordinates(current.getX() - 1, current.getY()).isInTab(toTest)
            && !Coordinates(current.getX() - 1, current.getY()).isInTab(alreadyTested)) {
            toTest.push_back(Coordinates(current.getX() - 1, current.getY()));
        }

        if (current.getY() >= 1 && game.getStone(current.getX(), current.getY() - 1) == color &&
            !Coordinates(Coordinates(current.getX(), current.getY() - 1)).isInTab(toTest)
            && !Coordinates(Coordinates(current.getX(), current.getY() - 1)).isInTab(alreadyTested)) {
            toTest.push_back(Coordinates(current.getX(), current.getY() - 1));
        }
        if (current.getX() + 1 < game.getSize() && game.getStone(current.getX() + 1, current.getY()) == color &&
            !Coordinates(current.getX() + 1, current.getY()).isInTab(toTest)
            && !Coordinates(current.getX() + 1, current.getY()).isInTab(alreadyTested)) {
            toTest.push_back(Coordinates(current.getX() + 1, current.getY()));
        }
        if (current.getY() + 1 < game.getSize() && game.getStone(current.getX(), current.getY() + 1) == color &&
            !Coordinates(current.getX(), current.getY() + 1).isInTab(toTest)
            && !Coordinates(current.getX(), current.getY() + 1).isInTab(alreadyTested)) {
            toTest.push_back(Coordinates(current.getX(), current.getY() + 1));
        }


        if (connexeVide(current.getX(), current.getY()))
            return 0;

        alreadyTested.push_back(Coordinates(current.getX(), current.getY()));
    } while (!toTest.empty());


    unsigned int nbPionsToRemove = alreadyTested.size();
    for (vector<Coordinates>::const_iterator it = alreadyTested.begin(); it != alreadyTested.end(); ++it)
        game.editStone(it->getX(), it->getY(), EMPTY);
    return nbPionsToRemove;
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

//boost::asio::io_service io_service;
//
//tcp::socket s(io_service);
//tcp::resolver resolver(io_service);
//boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));
//
//std::cout << "Enter message: ";
//char request[max_length];
//std::cin.getline(request, max_length);
//size_t request_length = std::strlen(request);
//boost::asio::write(s, boost::asio::buffer(request, request_length));
//
//char reply[max_length];
//size_t reply_length = boost::asio::read(s,
//                                        boost::asio::buffer(reply, request_length));
//std::cout << "Reply is: ";
//std::cout.write(reply, reply_length);
//std::cout << "\n";
