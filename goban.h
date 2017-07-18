#ifndef GOBAN_H_
#define GOBAN_H_

#include<vector>
#include "intersection.h"


using namespace std;

class Goban {
public:

    Goban();

    ~Goban();

    unsigned int getTaille() const;

    unsigned int access(unsigned int x, unsigned int y) const;

    void createGoban(unsigned int cote);

    enumIntersection getPion(unsigned int x, unsigned int y) const;

    void editPion(unsigned int x, unsigned int y, char valeur);

private:

    vector<Intersection> plateau;
    unsigned int taille;

};


#endif /* GOBAN_H_ */
