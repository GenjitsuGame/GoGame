#ifndef JOUEUR_H_
#define JOUEUR_H_

class Joueur {
public:

    Joueur();

    unsigned int getScore() const;

    void addScore(unsigned int newscore);


private:

    unsigned int score;
};

#endif /* JOUEUR_H_ */
