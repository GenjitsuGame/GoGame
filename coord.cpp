#include "coord.h"

using namespace std;

Coord::Coord(unsigned int x1, unsigned int y1) {
    x = x1;
    y = y1;
}

void Coord::editCoord(unsigned int x1, unsigned int y1) {
    x = x1;
    y = y1;
}

unsigned int Coord::getX() const {
    return x;
}

unsigned int Coord::getY() const {
    return y;
}

void Coord::operator=(const Coord &c) {
    x = c.getX();
    y = c.getY();
}

bool Coord::presentDsTab(const vector<Coord> &aTeste) const {
    for (vector<Coord>::const_iterator it = aTeste.begin(); it != aTeste.end(); ++it) {
        if (*this == *it)
            return true;
    }
    return false;
}

bool Coord::operator==(const Coord &a) const {
    return (getX() == a.getX() && getY() == a.getY());
}
