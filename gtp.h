/**
 * @file gtp.h
 * Projet GoGame
 * @author LE Victor, LUTTGENS Pascal
 * @version 1 - 08/03/2014
 * @brief Classe GTP gérant les entrées/sorties
 * Permet de d'executer tous les test unitaires.
 */

#ifndef GTP_H_
#define GTP_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "go.h"

using namespace std;

class GTP
{
public:
	GTP();

	/**
	 * @brief Appel une fonction selon la commande entrée
	 * @see list_command()
	 */
	void commandes();

    /**
     * @brief Test la valeur d'une intersection
     * @param[in] coord : les coordonnées de l'intersection à tester
     */
    void show(const string& coord) const;

	/**
	 * @brief Affiche toutes les commandes reconnues par le programme
	 */
	void list_command() const;

	/**
	 * @brief Affiche l'écran de victoire et recrée un nouveau
	 * goban de la taille du goban précédant.
	 * @see commandes()
	 * @see showboard()
	 * @param[in] : le joueur victorieux
	 */
	void showwin(char joueur);

	/**
	 * @brief Créé un plateau de taille x*x
	 * @param[in] size : taille d'un coté
	 */
	void boardsize(unsigned int size);

	/**
	 * @brief Affiche le plateau à l'écran
	 * @see showwin()
	 */
	void showboard() const;

	static void tester()
	{
	    Go::tester();
	    Goban::tester();
	    Intersection::tester();
	    Coord::tester();
	    Joueur::tester();

	    cout<<endl<<endl;
	    system("pause");
	    system("cls");
	}

private:

	Go gogame;
};

#endif /* GTP_H_ */
