#ifndef USER_TYPE_H
#define USER_TYPE_H

#include <QImage>
#include <QRect>
#include "cmr_pokemon.h"

class User_type
{
public:
    User_type();
    virtual ~User_type();
public:
    //all movement capabilty
    virtual void resetState();
    virtual void move();
    virtual void setDx(int);
    virtual void setDy(int);
    virtual int getDx();
    virtual int getDy();
    //collision and image data
    QRect getRect();
    QImage & getImage();
    //used for pausing the overworld window
    void setFightOpen(bool);
    bool getFightOpen();
    //getters
    pokemon *getPokemon(int i);
    int getPartySize();
    void print();
    protected:
    //image and collision data
    QImage image;
    QRect rect;
    //location data
    int dx,dy;
    //used for pausing
    bool fightopen;
    //helpful for initialization
    static const int partySize = 3;
    pokemon * party[partySize];
    static const int INITIAL_X = 180;
    static const int INITIAL_Y = 180;

};

#endif // USER_TYPE_H
