/**
 * @file goban.h
 * Projet GoGame
 * @author LE Victor, LUTTGENS Pascal
 * @version 1 - 08/03/2014
 * @brief Classe Goban repr�sentant le plateau de jeu.
 * Celui-ci est stock� dans un vector de taille : ar�te*ar�te.
 */

#ifndef GOBAN_H_
#define GOBAN_H_

#include<vector>
#include "intersection.h"
#include "unittest.h"

using namespace std;

/**
 * @class Intersection
 * @brief Classe repr�sentant une intersection de Goban.
 */
class Goban
{
public:

    /**
     * @fn Goban::Goban()
     * @brief Constructeur initialisant un Goban de taille 19.
     */
	Goban();

	/**
     * @fn Goban::~Goban()
     * @brief Deconstructeur de la classe Goban.
     * V�rifie si le plateau de jeu est vide.
     */
	~Goban();

    /**
     * @fn unsigned int Goban::getTaille() const
     * @brief Accesseur sur taille.
     * @param[out] : la taille du plateau de jeu.
     */
	unsigned int getTaille() const;

    /**
     * @fn unsigned int Goban::access() const
     * @brief Convertit des coordonn�es enti�res en indice pour
     * le vector plateau.
     * @see getTaille()
     * @param[in] x,y : couple de coordonn�es
     * @param[out]    : indice entier.
     * @pre x<taille et y<taille.
     * @post l'indice renvoy� est <(taille)�.
     */
    unsigned int access(unsigned int x, unsigned int y) const;

    /**
     * @fn void Goban::createGoban(unsigned int const cote)
     * @brief Cr�e un nouveau plateau de jeu de la taille donn�e.
     * @see Goban()
     * @param[in] cote : longueur d'une ar�te de Goban
     * @pre cote>0 et cote cote<20
     */
	void createGoban(unsigned int cote);

    /**
     * @fn enumIntersection Goban::getPion(unsigned int const x, unsigned int const y) const
     * @brief R�cupere la valeur d'une intersection sur le plateau � des coordonn�es donn�es.
     * @see access()
     * @param[in] x,y : couple de coordonn�e.
     * @param[out]    : valeur de l'intersection.
     * @pre x<taille et y<taille
     */
	enumIntersection getPion(unsigned int x, unsigned int y) const;

	/**
	 * @fn void editPion(unsigned int const x, unsigned int const y, char const valeur)
	 * @brief Change la valeur d'une intersection du plateau.
	 * @see access()
	 * @param[in] x,y    : couple de coordonn�e.
	 * @param[in] valeur : nouvelle valeur prise par l'intersection
	 * @pre x<taille et y<taille
	 */
	void editPion(unsigned int x, unsigned int y, char valeur);

    static void tester()
    {
        Goban goban;
        assertEquals(goban.getTaille(), (unsigned int)19, "Taille du Goban");
        assertEquals(goban.access(5,5), (unsigned int)100, "Conversion de couple de coordonn�es en Indice" );

        goban.editPion(5,5, 'N');
        assertEquals(goban.getPion(5,5),NOIR, "Mutateur et Accesseur externes de Intersection");
    }
private:

	vector<Intersection> plateau;    /**< vector contenant les intersections formant le plateau de jeu. */
	unsigned int taille;             /**< Nombre d'intersections formant une ar�te de Goban. */

};


#endif /* GOBAN_H_ */
