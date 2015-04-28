/**
* @file intersection.h
* Projet GoGame
* @author LE Victor, LUTTGENS Pascal
* @version 1 - 08/03/2014
* @brief Classe Intersection représentant
* Permet de tester et manipuler les intersection du Goban.
*/

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "unittest.h"

/**
* @enum enumIntersection
* @brief Enumérations des différentes valeurs
* qu'une intersection de Goban peut prendre.
*/
enum enumIntersection{
    VIDE,           /**< L'Intersection n'est pas occupée par un pion. */
    BLANC='B',      /**< L'intersection est occupée par un pion du joueur blanc. */
    NOIR='N'        /**< L'intersection est occupée par un pion du joueur noir. */
};

/**
* @class Intersection
* @brief Classe représentant une intersection de Goban.
*/
class Intersection
{
public:

    /**
    * @fn Intersection::Intersection()
    * @brief Constructeur de la classe Intersection,
    * Initialise les intersection à VIDE.
    */
	Intersection();

	/**
    * @fn Intersection::Intersection(char tour)
    * @brief Constructeur surchargé de la classe Intersection.
    * Initialise la valeur de l'intersection.
    * @param[in] tour : couleur du pion occupant l'intersection.
    */
	Intersection(char tour);

	/**
    * @fn enumIntersection Intersection::getPion() const
    * @brief Méthode qui permet de savoir ce que contient
    * l'intersection d'un goban.
    * @param[out] : ce que contient l'intersection testée.
    */
	enumIntersection getPion() const;

    /**
    * @fn void Intersection::edit(enumIntersection const valeur)
    * @brief Méthode qui permet de changer la valeur d'une
    * intersection.
    * @param[in] valeur : nouvelle valeur de l'intersection.
    */
	void edit(const enumIntersection& valeur);

	static void tester()
	{
	    Intersection intersection;
	    assertEquals(intersection.getPion(),VIDE, "Constructeur d'Intersection");

	    Intersection newintersection('N');
	    assertEquals(newintersection.getPion(),BLANC, "Constructeur surchargé d'Intersection");

	    intersection.edit(BLANC);
	    assertEquals(newintersection.getPion(),intersection.getPion(), "Changement de valeur d'Intersection");
	}

private:

	enumIntersection intersection; /** <Membre privé de la classe intersection stockant la valeur de ce qu'elle contient. */
};


#endif /* INTERSECTION_H_ */
