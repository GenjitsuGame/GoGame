#include "intersection.h"

Intersection::Intersection()
{
	intersection = VIDE;
}

Intersection::Intersection(char tour)
{
    intersection = (tour == 'N' ? BLANC : NOIR);
}

enumIntersection Intersection::getPion() const
{
	return intersection;
}

void Intersection::edit(const enumIntersection& valeur)
{
	intersection = valeur;
}
