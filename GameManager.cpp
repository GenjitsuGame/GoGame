#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "GameManager.h"


using namespace std;

GameManager::GameManager() {

}

void reply(const char *reponse) {
    cout << reponse;
}

void GameManager::cmds() {
    string command;
    static bool whiteTurn = false;
    enum {
        taille = 100
    };
    char line[taille];

    cin.getline(line, taille);
    istringstream iss(line);
    iss >> command;
    if (!iss) {
        iss.clear();
        reply("? unknown command\n\n");
    }
    if (command == "quit")
        exit(0);
    else if (command == "show") {
        string coord;
        iss >> coord;
        show(coord);
    } else if (command == "showBoard") {
        showBoard();
        reply("=\n\n");
    } else if (command == "list_commands")
        listCommands();
    else if (command == "clear_board") {
        gogame.createGoban(gogame.getSize());
        gogame.addMove("clear", "");
        whiteTurn = false;
        reply("= Goban reinitialise !\n\n");
        gogame.newMoveList();
    } else if (command == "liste_coup") {
        if (gogame.getMoveNbr() == 0)
            reply("Il n'y a pas de coups jou�s\n\n");
        else {
            for (unsigned int i = 0; i < gogame.getMoveNbr(); ++i)
                cout << gogame.getMove(i) << endl;
        }
    } else if (command == "forfeit") {
        string player;
        iss >> player;
        if (!iss)
            reply("? invalid argument\n\n");
        else {
            if (player != "B" && player != "W")
                reply("La couleur est incorrecte, veuillez rentrez W pour Blanc et B pour Noir\n");
            player == "B" ? showWinners('W') : showWinners('B');
        }
    } else if (command == "boardSize") {
        int size = 0;
        iss >> size;
        if (!iss)
            reply("? invalid argument\n\n");
        else {
            reply("=\n\n");
            boardSize(size);
        }
    } else if (command == "komi") {
        int komi = 0;
        iss >> komi;
        if (!iss)
            reply("? invalid argument\n\n");
        else {
            if (gogame.setKomi(komi))
                reply("\nLe komi a ete mis a jour !\n\n");
            else
                reply("\nKomi invalide !\n\n");
        }

    } else if (command == "set_winscore") {
        unsigned int scoretowin = 20;
        iss >> scoretowin;
        if (!iss)
            reply("? invalid argument\n\n");
        else {
            if (!gogame.setWinScore(scoretowin))
                reply("? invalid argument\n\n");
            else
                reply("\nLe score requis pour gagner � bien ete mis � jour !\n\n");
        }
    } else if (command == "play") {
        string player;
        string move;
        iss >> player >> move;
        if (!iss)
            reply("? invalid argument\n\n");
        else {
            if (player != "B" && player != "W")
                reply("La couleur est incorrecte, veuillez rentrez W pour Blanc et B pour Noir\n");
            else {
                if (player == "B" && whiteTurn)
                    reply("C'est au tour des Blancs de jouer\n");
                else if (player == "W" && !whiteTurn)
                    reply("C'est au tour des Noirs de jouer\n");
                else {
                    if (gogame.putStone(player[0], move) == false)
                        reply("Coordonn�es invalides\n");
                    else {
                        gogame.putStone(player[0], move);
                        gogame.addMove(player, move);

                        if (whiteTurn) whiteTurn = false;
                        else whiteTurn = true;

                        showBoard();

                        if (gogame.isWinner(player[0]))
                            showWinners(player[0]);
                    }
                    reply("=\n\n");
                }
            }
        }
    } else
        reply("? unknown command\n\n");
}

void GameManager::show(const string &coord) const {
    if (!gogame.isInGoban(coord))
        reply("\n= coordonnees invalides\n\n");
    else {
        if (gogame.getPion(coord) == WHITE)
            reply("\n= Blanc\n\n");
        else if (gogame.getPion(coord) == BLACK)
            reply("\n= Noir\n\n");
        else
            reply("\n= Vide\n\n");
    }
}

void GameManager::listCommands() const {
    reply(
            "Liste des commandes :\n\nlist_commands\nclear_board\nshow\nshowBoard\nboardSize\nkomi\nset_winscore\nplay\nforfeit\nliste_coup\n\n");
}

void GameManager::showWinners(char joueur) {
    reply("\n\n");
    showBoard();
    reply("Victoire du joueur ");
    reply(joueur == 'W' ? "WHITE" : "BLACK");
    reply("\n\n");
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

    reply("\n\n");
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

    cout << "O : White Player a : " << gogame.getScore('B') << " points." << endl;
    cout << "X : Black Player a : " << gogame.getScore('N') << " points." << endl;
    cout << "\n\n";
}
