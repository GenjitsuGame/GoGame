/**
 * @file coord.h
 * Projet GoGame
 * @author LE Victor, LUTTGENS Pascal
 * @version 1 - 08/03/2014
 * @brief Classe Coord représentant les coordonnées d'un pion.
 * Permet de tester la validité d'un coup, et de vérifier l'état d'une intersection.
 */

#ifndef COORD_H_
#define COORD_H_

#include "unittest.h"
#include <vector>

/**
 * @class Coord
 * @brief Classe permettant la manipulation de coordonnées
 * sous la forme (x,y) avec x et y deux entiers.
 */
class Coord
{

public:

    /**
     * @fn Coord::Coord(unsigned int const x1, unsigned int const y1)
     * @brief Initialise un couple de coordonnées
     * avec les valeurs données en paramètre.
     * @param[in] x1, y1 : le couple de coordonnées
     */
	Coord(unsigned int const x1, unsigned int const y1);

	/**
     * @fn void Coord::editCoord(unsigned int x1, unsigned int y1)
     * @brief Edite un couple de coordonnées
     * avec les valeurs données en paramètre.
     * @param[in] x1, y1 : le couple de coordonnées
     */
	void editCoord(unsigned int x1, unsigned int y1);

    /**
     * @fn unsigned int Coord::getX() const
     * @brief Accesseur sur la valeur de l'abscisse.
     * @param[out] : la valeur de l'abscisse
     */
	unsigned int getX() const;

	/**
     * @fn unsigned int Coord::getY const
     * @brief Accesseur sur la coordonnée en ordonnée.
     * @param[out] : la valeur de l'ordonnée
     */
	unsigned int getY() const;

	/**
     * @fn void Coord::operator=(Coord const& c)
     * @brief Surcharge de l'opérateur '='.
     * @param[in] c : un objet Coord
     */
	void operator=(const Coord& c);

    /**
     * @fn bool presentDsTab(std::vector<Coord> const& aTeste)
     * @brief Test si un couple de coordonnées est présent dans un vector donné.
     * @param[in] aTeste : le vector de Coord à parcourir
     * @param[out] : true si le couple de coordonnées à été trouvé dans le vector
     */
	bool presentDsTab(const std::vector<Coord>& aTeste) const;

	/**
     * @fn friend bool Coord::operator==(Coord const& a, Coord const& b) const
     * @brief Surcharge de l'opérateur '=='.
     * @param[in] a,b : les objets Coord à comparer
     * @param[out] : true si a et b sont identiques
     */
	bool operator==(const Coord& a) const;

    static void tester()
    {
    Coord coord(2,5);
    assertEquals(coord.getX(),(unsigned int)2, "Coord X");
    assertEquals(coord.getY(),(unsigned int)5, "Coord Y");

    coord.editCoord(6,4);
    assertEquals(coord.getX(),(unsigned int)6, "Coord X apres editCoord()");
    assertEquals(coord.getY(),(unsigned int)4, "Coord Y apres editCoord()");

    Coord newCoord(1,1);
    newCoord=coord;
    assertEquals(coord.getX(), newCoord.getX(), "Operator= pour Coord X");
    assertEquals(coord.getY(), newCoord.getY(), "Operator= pour Coord Y");
    assertTrue(coord==newCoord, "Operator==");
    }

private:

    unsigned int x; /**< Coordonnée X */
	unsigned int y; /**< Coordonnée Y */
};

#endif /* COORD_H_ */
