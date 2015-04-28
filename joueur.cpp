/**
* @file joueur.cpp
* Projet GoGame
* @author LE Victor, LUTTGENS Pascal
* @version 1 - 08/03/2014
* @brief Classe repr�sentant un joueur.
* Permet de g�r� les donn�es relatives aux scores.
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
