#ifndef PLAYER_H
#define PLAYER_H
#include <QImage>
#include <QRect>
#include "cmr_pokemon.h"
#include "cmr_user_type.h"

class Player : public User_type
{
public:
    Player();
    ~Player();
public:
    //all movement capabilty, virtual
    void resetState();
    void move();
    void setDx(int);
    void setDy(int);
    int getDx();
    int getDy();

};

#endif // PLAYER_H
