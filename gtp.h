#ifndef GTP_H_
#define GTP_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "go.h"

using namespace std;

class GTP {
public:
    GTP();

    void commandes();

    void show(const string &coord) const;

    void list_command() const;

    void showwin(char joueur);

    void boardsize(unsigned int size);

    void showboard() const;

private:

    Go gogame;
};

#endif /* GTP_H_ */
