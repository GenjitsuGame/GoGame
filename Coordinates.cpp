#include "Coordinates.h"

using namespace std;

Coordinates::Coordinates(unsigned int x1, unsigned int y1) {
    x = x1;
    y = y1;
}

void Coordinates::editCoord(unsigned int x1, unsigned int y1) {
    x = x1;
    y = y1;
}

unsigned int Coordinates::getX() const {
    return x;
}

unsigned int Coordinates::getY() const {
    return y;
}

void Coordinates::operator=(const Coordinates &c) {
    x = c.getX();
    y = c.getY();
}

bool Coordinates::isInTab(const vector<Coordinates> &aTeste) const {
    for (vector<Coordinates>::const_iterator it = aTeste.begin(); it != aTeste.end(); ++it) {
        if (*this == *it)
            return true;
    }
    return false;
}

bool Coordinates::operator==(const Coordinates &a) const {
    return (getX() == a.getX() && getY() == a.getY());
}
