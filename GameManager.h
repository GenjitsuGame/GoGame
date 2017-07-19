#ifndef GTP_H_
#define GTP_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "Go.h"

using namespace std;

class GameManager {
public:
    GameManager();

    void cmds();

    void show(const string &coord) const;

    void listCommands() const;

    void showWinners(char joueur);

    void boardSize(unsigned int size);

    void showBoard() const;

private:

    Go gogame;
};

#endif /* GTP_H_ */
