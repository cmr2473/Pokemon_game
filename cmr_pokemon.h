#ifndef POKEMON_H
#define POKEMON_H

#include "cmr_attack.h"
#include <iostream>
#include <string>
using namespace std;
class pokemon
{
public:
    pokemon(int);
    pokemon();
    ~pokemon();

    int getHealth();
    int getDefence();
    int getPower();
    int getnumber();
    void setnumber(int i);
    void setHealth(int);
    void setDefence(int);
    void setPower(int);
    void setName(string);
    void turn(attack * move, pokemon * p);
    void setMove(int, int);
    string getName();
    attack * getMove(int);
    string getSprite(int s);
    void setSprite(int s, string i);

protected:
    int numberInList;
    string name;
    int health;
    int defence;
    int power;
    attack *moves[4];
    string sprite[2];
};
#endif // POKEMON_H
