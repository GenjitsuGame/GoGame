#ifndef JOUEUR_H_
#define JOUEUR_H_

/**
* @file joueur.h
* Projet GoGame
* @author LE Victor, LUTTGENS Pascal
* @version 1 - 08/03/2014
* @brief Classe représentant un joueur.
* Permet de géré les données relatives aux scores.
*/

#include "unittest.h"

/**
* @class Joueur
* @brief Représente un joueur en mémoire en stockant les informations sur son score
*/
class Joueur
{
public:

    /**
     * @fn Joueur::Joueur();
     * @brief Constructeur de la classe Joueur.
     * Initialise par défaut les scores à 0.
     */
	Joueur();

	/**
	 * @fn unsigned int Joueur::getScore() const
	 * @brief Accesseur sur le score d'un joueur.
	 * @param[out] : le score du joueur
	 */
	unsigned int getScore() const;

	/**
	 * @fn void addScore(unsigned int const newscore)
	 * @brief Mutateur sur le score d'un joueur.
	 * Ajoute le score donné en paramètre au score actuel.
	 * @param[in] : le nouveau score du joueur
	 */
	void addScore(unsigned int newscore);

    static void tester()
    {
        Joueur joueur;
        assertEquals(joueur.getScore(),(unsigned int)0, "Constructeur de Joueur");

        joueur.addScore(2);
        assertEquals(joueur.getScore(),(unsigned int)2, "Mutateur de Score");
    }

private:

	unsigned int score; /**< Le score du joueur */
};

#endif /* JOUEUR_H_ */
