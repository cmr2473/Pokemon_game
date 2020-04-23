#ifndef PLAYER_H
#define PLAYER_H



#include <QImage>
#include <QRect>
#include "cmr_pokemon.h"
#define POKECOUNT 3
class Player
{
public:
    Player();
    ~Player();
public:
    void resetState();
    void move();
    void setDx(int);
    void setDy(int);
    int getDx();
    int getDy();
    QRect getRect();
    QImage & getImage();
    void setFightOpen(bool);
    bool getFightOpen();
    pokemon *getPokemon(int i);
    pokemon addPokemon();
    int getPartySize();
private:
    static const int partySize = 3;
    QImage image;
    QRect rect;
    int dx,dy;
    bool fightopen;
    pokemon * party[partySize];
    static const int INITIAL_X = 180;
    static const int INITIAL_Y = 180;

};

#endif // PLAYER_H
