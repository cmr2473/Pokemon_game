#ifndef ATTACK_H
#define ATTACK_H
#include <iostream>
#include <string>
using namespace std;

class attack
{
public:
    attack();
    attack(int attackNumber);
    attack(string n, int d, int pop,int dop,int sp,int sd, int dia);
    int getDamage();
    int getPowerOp();
    int getDefenceOp();
    int getPowerSelf();
    int getDefenceSelf();
    int getDialogue();
    string getname();

    void setName(string);
private:
    string name;
    int damage;
    int powerOp;
    int defenceOp;
    int selfPower;
    int selfDefence;
    int dialogue;

};
#endif // ATTACK_H
