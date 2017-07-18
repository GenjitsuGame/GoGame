#ifndef COORD_H_
#define COORD_H_

#include <vector>

class Coordinates {

public:

    Coordinates(unsigned int const x1, unsigned int const y1);

    void editCoord(unsigned int x1, unsigned int y1);

    unsigned int getX() const;


    unsigned int getY() const;

    void operator=(const Coordinates &c);

    bool isInTab(const std::vector<Coordinates> &aTeste) const;

    bool operator==(const Coordinates &a) const;

private:

    unsigned int x;
    unsigned int y;
};

#endif /* COORD_H_ */
