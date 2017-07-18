#ifndef INTERSECTION_H_
#define INTERSECTION_H_


enum enumIntersection {
    VIDE,
    BLANC = 'B',
    NOIR = 'N'
};

class Intersection {
public:
    Intersection();

    Intersection(char tour);

    enumIntersection getPion() const;

    void edit(const enumIntersection &valeur);

private:

    enumIntersection intersection; /** <Membre priv� de la classe intersection stockant la valeur de ce qu'elle contient. */
};


#endif /* INTERSECTION_H_ */
