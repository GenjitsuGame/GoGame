/**
* @file intersection.cpp
* Projet GoGame
* @author LE Victor, LUTTGENS Pascal
* @version 1 - 08/03/2014
* @brief Classe Intersection représentant
* Permet de tester et manipuler les intersection du Goban.
*/

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
