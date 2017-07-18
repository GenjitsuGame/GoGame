#ifndef COORD_H_
#define COORD_H_

#include <vector>

class Coord {

public:

    Coord(unsigned int const x1, unsigned int const y1);

    void editCoord(unsigned int x1, unsigned int y1);

    unsigned int getX() const;


    unsigned int getY() const;

    void operator=(const Coord &c);

    bool presentDsTab(const std::vector<Coord> &aTeste) const;

    bool operator==(const Coord &a) const;

private:

    unsigned int x;
    unsigned int y;
};

#endif /* COORD_H_ */
