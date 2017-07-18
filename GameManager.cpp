#include <iostream>
#include <cstdlib>
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {

}

void repondre(const char *reponse) {
    cout << reponse;
}

void GameManager::cmds() {
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
    } else if (command == "showBoard") {
        showBoard();
        repondre("=\n\n");
    } else if (command == "list_commands")
        listCmds();
    else if (command == "clear_board") {
        gogame.createGoban(gogame.getSize());
        gogame.addMove("clear", "");
        repondre("= Goban reinitialise !\n\n");
        gogame.newMoveList();
    } else if (command == "liste_coup") {
        if (gogame.getMoveNbr() == 0)
            repondre("Il n'y a pas de coups jou�s\n\n");
        else {
            for (unsigned int i = 0; i < gogame.getMoveNbr(); ++i)
                cout << gogame.getMove(i) << endl;
        }
    } else if (command == "boardSize") {
        int size = 0;
        iss >> size;
        if (!iss)
            repondre("? invalid argument\n\n");
        else {
            repondre("=\n\n");
            boardSize(size);
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
                    if (gogame.putStone(joueur[0], coup) == false)
                        repondre("Coordonn�es invalides\n");
                    else {
                        gogame.putStone(joueur[0], coup);
                        gogame.addMove(joueur, coup);

                        if (tourBlanc) tourBlanc = false;
                        else tourBlanc = true;

                        showBoard();

                        if (gogame.isWinner(joueur[0]))
                            showWinners(joueur[0]);
                    }
                    repondre("=\n\n");
                }
            }
        }
    } else
        repondre("? unknown command\n\n");
}

void GameManager::show(const string &coord) const {
    if (!gogame.isInGoban(coord))
        repondre("\n= coordonnees invalides\n\n");
    else {
        if (gogame.getPion(coord) == WHITE)
            repondre("\n= Blanc\n\n");
        else if (gogame.getPion(coord) == BLACK)
            repondre("\n= Noir\n\n");
        else
            repondre("\n= Vide\n\n");
    }
}

void GameManager::listCmds() const {
    repondre(
            "= Liste des cmds :\n\nname\nprotocol_version\nversion\nlist_commands\nclear_board\nshow\nshowBoard\nboardSize\nkomi\nset_winscore\nplay\nliste_coup\n\n");
}

void GameManager::showWinners(char joueur) {
    repondre("\n\n");
    showBoard();
    repondre("Victoire du joueur ");
    repondre(joueur == 'B' ? "WHITE" : "BLACK");
    repondre("\n\n");
    system("pause");
    system("cls");
    gogame.createGoban(gogame.getSize());
    gogame.newMoveList();
}

void GameManager::boardSize(unsigned int size) {
    if (size > 0 && size > 19) {
        cout << "Veuillez rentrez une size compris entre 1 et 19" << endl;
        return;
    }

    gogame.createGoban(size);
}

void GameManager::showBoard() const {
    vector<char> col;
    for (unsigned int i = 0; i <= gogame.getSize(); i++) {
        if ((char) (65 + i) != 'I')
            col.push_back((char) (65 + i));
    }
    col.resize(gogame.getSize());

    repondre("\n\n");
    for (unsigned int y = 0; y < gogame.getSize(); y++) {
        stringstream ss;
        ss << (y + 1);
        string tmp = ss.str();
        if (y != 0)
            cout << (tmp.size() == 1 ? " " : "") << tmp;
        for (unsigned int x = 0; x < gogame.getSize(); x++) {
            cout << " ";
            if (y == 0 && x == 0) {
                cout << "  ";
                for (vector<char>::const_iterator it = col.begin(); it < col.end(); ++it)
                    cout << *it << " ";
                cout << endl << " 1 ";
            }

            if (gogame.getStone(x, y) == WHITE)
                cout << 'O';
            else if (gogame.getStone(x, y) == BLACK)
                cout << 'X';
            else
                cout << '.';
        }
        cout << endl;
    }

    cout << "O : Player Blanc a : " << gogame.getScore('B') << " points." << endl;
    cout << "X : Player Noir  a : " << gogame.getScore('N') << " points." << endl;
    cout << "\n\n";
}
