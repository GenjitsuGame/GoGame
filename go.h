/**
 * @file go.cpp
 * Projet BPO : Le jeu de Go
 * @author LE Victor, LUTTGENS Pascal groupe 103
 * @version 1 - 15/02/13
 * @brief Composant Go
 */

#ifndef GO_H_
#define GO_H_


#include <iostream>

#include "joueur.h"
#include "goban.h"
#include "coord.h"
#include "unittest.h"

using namespace std;



class Go
{
public:

	Go();
	~Go();

	/**
	 * @brief Cr�e le goban
	 * @param[in] f : la taille du Goban
	 */
	void createGoban(unsigned int size);

	/**
	 * @brief R�cup�re le pion de position (x,y)
	 * @param[in] x : coordonn�e x
	 * @param[in] y : coordonn�e y
	 * @param[out] : le pion retourn�
	 */
	enumIntersection getPion(unsigned int x, unsigned int y) const;

    /**
	 * @brief R�cup�re la taille du Goban
	 * @param[out] : la taille du Gobab
	 */
	unsigned int getTaille() const;

	/**
	 * @brief R�cup�re le score d'un Joueur
	 * @param[in] couleur : la couleur du Joueur
     * @param[out] : le score du Joueur
     */
     unsigned int getScore(char couleur) const;

	/**
	 * @brief Permet de savoir si un joueur a gagn� la partie
	 * @param[in] couleur : la couleur du Joueur
     * @param[out] : True si le joueur a gagn�
     */
     bool isWinner(char couleur) const;

    /**
	 * @brief Accesseur sur le membre priv� winScore.
     * @param[out] : le score requis pour gagner
     */
     unsigned int getWinScore() const;

     /**
	 * @brief Mutateur sur le membre priv� winScore.
     * @param[in] newwinscore : le nouveau score requis pour gagner
     * @param[out] : true si le nouveau score est autoris�.
     * @pre 0<newwinscore<=3
     */
     bool setWinScore(unsigned int newwinscore);

    /**
     * @brief Change la valeur du komi.
     * @see getWinScore()
     * @param[in] komi : valeur du komi
     * @param[out] : true si la valeur du komi est autoris�
     * @pre komi<0 et komi<WinScore
     **/
     bool setKomi(unsigned int komi);

	/**
	 * @brief Convertit des coordonn�es de type string en type Coord
	 * @see getTaille()
	 * @param[in] coord : coordonn�es en string
	 * @param[out] : coordonn�es en Coord
	 */
	Coord conv(const string& coord) const;

	/**
	 * @brief Test si le pion de coordon�e "coord" est dans le Goban
     * @see conv()
     * @see getTaille()
	 * @param[in] coord : coordonn�e �crit en string comme "A1"
	 * @param[out] : True si le pion est dans le Goban False sinon
	 */
	bool estDansGoban(const string& coord) const;

	/**
	 * @brief Renvoie ce que contient la case de position coord
	 * @see conv()
     * @see getPion(uint, uint)
	 * @param[in] coord : coordonn�e �crit en string comme "A1"
	 * @param[out] : le pion renvoy� (BLANC ou NOIR ou VIDE)
	 */
	enumIntersection getPion(const string& coord) const;

	/**
	 * @brief Test si les cases connexes sont vide ou pas
	 * @param[in] x : coordonn�e x
	 * @param[in] y : coordonn�e y
	 * @param[out] : True si on trouve Vide dans l'une des cases connexes
	 * 				 False sinon
	 */
	bool connexeVide(unsigned int x, unsigned y);


	/**
	 * @brief Test si la chaine contenant le pion en (x,y) est entour�,
	 * Si oui, on supprime la chaine, sinon on ne fait rien
	 * @param[in] x : coordonn�e x
	 * @param[in] y : coordonn�e y
	 * @param[in] couleur : la couleur inverse du pion en (x,y)
	 * @param[out] : le nombre de pion supprim�
	 */
	unsigned int entoure(unsigned int x, unsigned int y, const enumIntersection& couleur);

	/**
	 * @brief Appel la fonction "entoure" pour les cases connexes au pion (x,y)
	 * @see la fonction entoure
	 * @param[in] x : coordonn�e x
	 * @param[in] y : coordonn�e y
	 * @param[in] tour : la couleur du pion (x,y)
	 * N pour Noir B pour Blanc
	 */
	unsigned int checkChaine(unsigned int x, unsigned y, char tour);


	/**
	 * @brief Joue un pion de couleur 'char couleur' � la position pos
	 * @see la fonction checkchaine
	 * @param[in] couleur : la couleur du pion jou�
	 * N pour Noir et B pour Blanc
	 * @param[in] pos : la coordon�e du pion
	 * B1 va correspondre � (1,0)
	 * @param[out] bool : True si la position est correcte
	 * 					  False sinon
	 */
	bool placerPion(char couleur, const string& pos);

    /**
     * @brief Accesseur renvoyant le nombre de coups jou�s.
     * @param[out] : nombre de coups jou�s dans la partie courante
     */
    unsigned int getNbCoups() const;

    /**
     * @brief Stock le dernier jou� coup en m�moire.
     * @param[in] joueur : le joueur courant
     * @param[in] coup : les coordonn�es du coup jou�
     */
    void addCoup(const string& joueur, const string& coup);

    /**
     * @brief Efface la liste de coup actuelle.
     */
    void newListeCoup();

    /**
     * @brief R�cup�re un coup dans la liste de coup actuelle.
     * @see getNbCoups()
     * @param|in] i : l'indice renseignant la position du coup dans la liste
     * @param[out] : le coup r�cup�r� dans la liste
     * @pre i<getNbCoups()
     */
    string getCoup(unsigned int i) const;

     static void tester()
     {
      Go go;
      go.createGoban(10);
      assertEquals(go.getTaille(),(unsigned int)10, "Taille");

      go.placerPion('B', "B2");
      assertEquals(go.getPion(1,1), BLANC, "Pion plac�");
      assertEquals(go.getPion("B2"), BLANC, "Pion plac�");
      assertEquals(go.connexeVide(1,1), true, "ConnexeVide");
      assertEquals(go.estDansGoban("B2"), true, "EstDansGoban");

      go.placerPion('N', "A2");
      go.placerPion('N', "B1");
      go.placerPion('N', "C2");
      go.placerPion('N', "B3");

      assertEquals(go.getPion(1,1), VIDE, "Pion supprim� OK");

      assertFalse(go.setKomi(2), "Komi sup�rieur au score requis pour gagner");
      assertTrue(go.setWinScore(3), "Modification autoris�e du score requis pour gagner");

      go.setWinScore(3);
      assertEquals(go.getWinScore(),(unsigned int)3, "Modification du score requis pour gagner");
      assertTrue(go.setKomi(2), "Komi autoris�");

      Coord coord(2,5);
      assertTrue(coord==go.conv("C6"), "Conversion de string coord en Coord coord");

      go.addCoup("B", "B4");
      go.addCoup("N", "A5");
      go.addCoup("B", "C2");
      go.addCoup("N", "A1");

      assertEquals(go.getNbCoups(), (unsigned int)4, "Nombre de coups jou�s");
      assertTrue(go.getCoup(2)=="B C2", "Stockage de coups jou�");

      go.newListeCoup();
      assertEquals(go.getNbCoups(), (unsigned int)0, "Effacement de la liste");
     }

private:

	Goban jeu;                  /**< Plateau de jeu */
	Joueur noir;                /**< Joueur contr�lant les pions noirs */
	Joueur blanc;               /**< Joueur controlant les pions blancs */
	unsigned int winScore;      /**< Score requis pour gagner une partie */
	vector<string> listeCoup;   /**< Liste des coups jou�s pendant la partie courante */
};




#endif /* GOBAN_H_ */
