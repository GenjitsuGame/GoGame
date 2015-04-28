/**
* @file joueur.cpp
* Projet GoGame
* @author LE Victor, LUTTGENS Pascal
* @version 1 - 08/03/2014
* @brief Classe représentant un joueur.
* Permet de géré les données relatives aux scores.
*/

#include "joueur.h"

Joueur::Joueur()
{
	score = 0;
}

unsigned int Joueur::getScore() const
{
	return score;
}

void Joueur::addScore(unsigned int newscore)
{
    score+=newscore;
}
