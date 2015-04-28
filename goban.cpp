/**
 * @file goban.cpp
 * Projet GoGame
 * @author LE Victor, LUTTGENS Pascal
 * @version 1 - 08/03/2014
 * @brief Classe Goban représentant le plateau de jeu.
 * Celui-ci est stocké dans un vector de taille : arête*arête.
 */

#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

#include "goban.h"


Goban::Goban()
{
    createGoban(19);
}


Goban::~Goban()
{

}

unsigned int Goban::getTaille() const
{
	return taille;
}

unsigned int Goban::access(unsigned int x, unsigned int y) const
{
    return getTaille()*y+x;
}

void Goban::createGoban(unsigned int cote)
{
	assert(cote<20 && cote > 0);
	if (!plateau.empty())
        plateau.clear();
	plateau.resize(cote*cote);
	taille = cote;
}


enumIntersection Goban::getPion(unsigned int x, unsigned int y) const
{
	assert(x<getTaille()&& y<getTaille());
	/*retourne la valeur de l'intersection à la position (x,y)*/
	return (plateau.at(access(x,y))).getPion();

}

void Goban::editPion(unsigned int x, unsigned int y, char valeur)
{
	assert(x<getTaille() && y<getTaille());
	/*édite la valeur de l'intersection à la position (x,y)*/
	(plateau.at(access(x,y))).edit((enumIntersection)valeur);
}
