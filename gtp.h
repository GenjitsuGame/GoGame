/**
 * @file gtp.h
 * Projet GoGame
 * @author LE Victor, LUTTGENS Pascal
 * @version 1 - 08/03/2014
 * @brief Classe GTP g�rant les entr�es/sorties
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
	 * @brief Appel une fonction selon la commande entr�e
	 * @see list_command()
	 */
	void commandes();

    /**
     * @brief Test la valeur d'une intersection
     * @param[in] coord : les coordonn�es de l'intersection � tester
     */
    void show(const string& coord) const;

	/**
	 * @brief Affiche toutes les commandes reconnues par le programme
	 */
	void list_command() const;

	/**
	 * @brief Affiche l'�cran de victoire et recr�e un nouveau
	 * goban de la taille du goban pr�c�dant.
	 * @see commandes()
	 * @see showboard()
	 * @param[in] : le joueur victorieux
	 */
	void showwin(char joueur);

	/**
	 * @brief Cr�� un plateau de taille x*x
	 * @param[in] size : taille d'un cot�
	 */
	void boardsize(unsigned int size);

	/**
	 * @brief Affiche le plateau � l'�cran
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
