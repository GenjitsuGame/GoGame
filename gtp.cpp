#include <iostream>
#include <cstdlib>
#include "gtp.h"

using namespace std;

GTP::GTP() {

}

void repondre(const char *reponse) {
    cout << reponse;
}

void GTP::commandes() {
    string command;
    enum {
        taille = 100
    };
    char line[taille];

    cin.getline(line, taille);
    istringstream iss(line);
    iss >> command;
    if (!iss) {
        iss.clear();
        repondre("? unknown command\n\n");
    }
    if (command == "quit")
        exit(0);
    else if (command == "name")
        repondre("= go\n\n");
    else if (command == "protocol_version")
        repondre("= 2\n\n");
    else if (command == "version")
        repondre("= 0.1\n\n");
    else if (command == "show") {
        string coord;
        iss >> coord;
        show(coord);
    } else if (command == "showboard") {
        showboard();
        repondre("=\n\n");
    } else if (command == "list_commands")
        list_command();
    else if (command == "clear_board") {
        gogame.createGoban(gogame.getTaille());
        gogame.addCoup("clear", "");
        repondre("= Goban reinitialise !\n\n");
        gogame.newListeCoup();
    } else if (command == "liste_coup") {
        if (gogame.getNbCoups() == 0)
            repondre("Il n'y a pas de coups jou�s\n\n");
        else {
            for (unsigned int i = 0; i < gogame.getNbCoups(); ++i)
                cout << gogame.getCoup(i) << endl;
        }
    } else if (command == "boardsize") {
        int size = 0;
        iss >> size;
        if (!iss)
            repondre("? invalid argument\n\n");
        else {
            repondre("=\n\n");
            boardsize(size);
        }
    } else if (command == "komi") {
        int komi = 0;
        iss >> komi;
        if (!iss)
            repondre("? invalid argument\n\n");
        else {
            if (gogame.setKomi(komi))
                repondre("\nLe komi a ete mis a jour !\n\n");
            else
                repondre("\nKomi invalide !\n\n");
        }

    } else if (command == "set_winscore") {
        unsigned int scoretowin = 1;
        iss >> scoretowin;
        if (!iss)
            repondre("? invalid argument\n\n");
        else {
            if (!gogame.setWinScore(scoretowin))
                repondre("? invalid argument\n\n");
            else
                repondre("\nLe score requis pour gagner � bien ete mis � jour !\n\n");
        }
    } else if (command == "play") {
        string joueur;
        string coup;
        iss >> joueur >> coup;
        if (!iss)
            repondre("? invalid argument\n\n");
        else {
            static bool tourBlanc = false;
            if (joueur != "N" && joueur != "B")
                repondre("La couleur est incorrecte, veuillez rentrez B pour Blanc et N pour Noir\n");
            else {
                if (joueur == "N" && tourBlanc)
                    repondre("C'est au tour des Blancs de jouer\n");
                else if (joueur == "B" && !tourBlanc)
                    repondre("C'est au tour des Noirs de jouer\n");
                else {
                    if (gogame.placerPion(joueur[0], coup) == false)
                        repondre("Coordonn�es invalides\n");
                    else {
                        gogame.placerPion(joueur[0], coup);
                        gogame.addCoup(joueur, coup);

                        if (tourBlanc) tourBlanc = false;
                        else tourBlanc = true;

                        showboard();

                        if (gogame.isWinner(joueur[0]))
                            showwin(joueur[0]);
                    }
                    repondre("=\n\n");
                }
            }
        }
    } else
        repondre("? unknown command\n\n");
}

void GTP::show(const string &coord) const {
    if (!gogame.estDansGoban(coord))
        repondre("\n= coordonnees invalides\n\n");
    else {
        if (gogame.getPion(coord) == BLANC)
            repondre("\n= Blanc\n\n");
        else if (gogame.getPion(coord) == NOIR)
            repondre("\n= Noir\n\n");
        else
            repondre("\n= Vide\n\n");
    }
}

void GTP::list_command() const {
    repondre(
            "= Liste des commandes :\n\nname\nprotocol_version\nversion\nlist_commands\nclear_board\nshow\nshowboard\nboardsize\nkomi\nset_winscore\nplay\nliste_coup\n\n");
}

void GTP::showwin(char joueur) {
    repondre("\n\n");
    showboard();
    repondre("Victoire du joueur ");
    repondre(joueur == 'B' ? "BLANC" : "NOIR");
    repondre("\n\n");
    system("pause");
    system("cls");
    gogame.createGoban(gogame.getTaille());
    gogame.newListeCoup();
}

void GTP::boardsize(unsigned int size) {
    if (size > 0 && size > 19) {
        cout << "Veuillez rentrez une taille compris entre 1 et 19" << endl;
        return;
    }

    gogame.createGoban(size);
}

void GTP::showboard() const {
    vector<char> col;
    for (unsigned int i = 0; i <= gogame.getTaille(); i++) {
        if ((char) (65 + i) != 'I')
            col.push_back((char) (65 + i));
    }
    col.resize(gogame.getTaille());

    repondre("\n\n");
    for (unsigned int y = 0; y < gogame.getTaille(); y++) {
        stringstream ss;
        ss << (y + 1);
        string tmp = ss.str();
        if (y != 0)
            cout << (tmp.size() == 1 ? " " : "") << tmp;
        for (unsigned int x = 0; x < gogame.getTaille(); x++) {
            cout << " ";
            if (y == 0 && x == 0) {
                cout << "  ";
                for (vector<char>::const_iterator it = col.begin(); it < col.end(); ++it)
                    cout << *it << " ";
                cout << endl << " 1 ";
            }

            if (gogame.getPion(x, y) == BLANC)
                cout << 'O';
            else if (gogame.getPion(x, y) == NOIR)
                cout << 'X';
            else
                cout << '.';
        }
        cout << endl;
    }

    cout << "O : Joueur Blanc a : " << gogame.getScore('B') << " points." << endl;
    cout << "X : Joueur Noir  a : " << gogame.getScore('N') << " points." << endl;
    cout << "\n\n";
}
