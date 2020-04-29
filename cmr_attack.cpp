#include "cmr_attack.h"
#include <iostream>
#include <fstream>
using namespace std;

attack::attack()
{   //default constructor, used in other constructors file processing.
    name = "n";
    damage = 1;
    powerOp = 1;
    defenceOp = 1;
    selfPower = 1;
    selfDefence = 1;
}

attack::attack(string n, int d, int pop,int dop,int sp,int sd, int dia){
    //constructor for taking things out of the file, sets individual values
    name = n;
    damage = d;
    powerOp = pop;
    defenceOp = dop;
    selfPower = sp;
    selfDefence = sd;
    dialogue = dia;
}

attack::attack(int attackNumber){
    //constructor used to pull attack info from file

    ifstream attackList;
    //opens attack data file
    attackList.open("attackList.txt");

    if (attackList.fail())
    {
        cout << "Error Opening attackList" << endl;
        exit(1);
    };//end if

    int numAttacks = 0;
    attackList >> numAttacks;
    //creates an array of attacks to find the attack we would like to initialize
    attack * attackArray[numAttacks];
    //temporary variables
    string n;
    int dam,pow,def,selfp,selfd,dia;
    //stores data from file into the attack array
    int i = 0;
    while (attackList >> n >> dam >> pow >> def >> selfp >> selfd >> dia){

        attackArray[i] = new attack(n,dam,pow,def,selfp,selfd,dia);
        i++;
    }
    //closes the file
    attackList.close();
    //transfers the wanted attack data into the class from the array
    this->name = attackArray[attackNumber]->getname();
    this->damage = attackArray[attackNumber]->getDamage();
    this->powerOp = attackArray[attackNumber]->getPowerOp();
    this->defenceOp = attackArray[attackNumber]->getDefenceOp();
    this->selfPower = attackArray[attackNumber]->getPowerSelf();
    this->selfDefence = attackArray[attackNumber]->getDefenceSelf();
    this->dialogue = attackArray[attackNumber]->getDialogue();
    //deletes the attacks in the array stored from the file
    for(int k = 0; k < numAttacks; k ++){
        delete attackArray[k];
    }

}
//*****************************************setters and getters
int attack::getDamage(){
    return damage;
}
int attack::getPowerOp(){
    return powerOp;
}

int attack::getDefenceOp(){
    return defenceOp;
}

int attack::getPowerSelf(){
    return selfPower;
}

int attack::getDefenceSelf(){
    return selfDefence;
}

string attack::getname(){
    return name;
}
int attack::getDialogue(){
    return dialogue;
}
