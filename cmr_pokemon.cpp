#include "cmr_pokemon.h"
#include "cmr_attack.h"

# include <iostream>
# include <fstream>
# include <iomanip>
#include <string>
#include <ctime>
using namespace std;

pokemon::pokemon(){
    health = 100;
    defence = 10;
    power = 10;
    name = "name";
    moves[0] = new attack ("n",0,0,0,0,0,0);
    moves[1] = new attack ("n",0,0,0,0,0,0);
    moves[2] = new attack ("n",0,0,0,0,0,0);
    moves[3] = new attack ("n",0,0,0,0,0,0);
    sprite[0] = "i.png";
    sprite[1] = "i.png";
}
pokemon::pokemon( int PokeNumber)
{

    int index = PokeNumber;

    ifstream pokeDex;
    pokeDex.open("Pokedex.txt");
    if (pokeDex.fail()){
        cout << "unable to open pokedex" << endl;
        exit(1);
    }
    int numPoke = 0;
    pokeDex >> numPoke;
    pokemon * Dex[numPoke];


    //cout << numPoke << "  " << Dex[0]->getName() << " " << Dex[0]->getHealth() << endl;


    int number;
    int h;
    int d;
    int p;
    string n;
    int move1, move2, move3,move4;
    string image_back;
    string image_front;

    int i =0;

    while(pokeDex >> number >> n >> h >> d >> p >> move1 >> move2 >> move3 >> move4 >> image_back>>image_front){
        Dex[i] = new pokemon();
        Dex[i]->setName(n);
        Dex[i]->setnumber(number);
        Dex[i]->setHealth(h);
        Dex[i]->setDefence(d);
        Dex[i]->setPower(p);
        Dex[i]->setSprite(0,image_back);
        Dex[i]->setSprite(1,image_front);

        Dex[i]->setMove(0, move1);
        Dex[i]->setMove(1, move2);
        Dex[i]->setMove(2, move3);
        Dex[i]->setMove(3, move4);

        i++;
        //cout << "t" ;
    }
    pokeDex.close();



    //cout << Dex[0]->getMove(1)->getDamage() << " "  << endl;
    this->numberInList = Dex[index]->getnumber();
    //cout << "j";
    this->name = Dex[index]->getName();
    //cout << getName();
    this->health = Dex[index]->getHealth();
    this->defence = Dex[index]->getDefence();
    this->power = Dex[index]->getPower();
    this->sprite[0] = Dex[index]->getSprite(0);
    this->sprite[1] = Dex[index]->getSprite(1);
    this->moves[0] = Dex[index]->getMove(0);
    this->moves[1] = Dex[index]->getMove(1);
    this->moves[2] = Dex[index]->getMove(2);
    this->moves[3] = Dex[index]->getMove(3);
    //cout << "welp" << endl;
    for(int k = 0 ; k < numPoke; k ++){
        delete Dex[k];
    }
}
pokemon::~pokemon(){

}

int pokemon::getHealth(){
    return health;
}
int pokemon::getDefence(){
    return defence;
}
int pokemon::getPower(){
    return power;
}
void pokemon::setPower(int p){
    power = p;
}
void pokemon::setHealth(int h){
    health = h;
}
void pokemon::setDefence(int d){
    defence = d;
}
void pokemon::turn(attack *move, pokemon *p){
    int totalDamage = ((float)(this->getPower()-p->getDefence())/100+1) * move->getDamage();
    if (rand()%1000 < 650){
        p->setHealth(p->getHealth() - totalDamage);
        p->setPower(p->getPower() + move->getPowerOp());
        p->setDefence(p->getDefence() + move->getDefenceOp());

        cout << getName() << " uses " << move->getname() << ". " << endl
             << "It hits " << p->getName() << " for " << totalDamage << " damage!" << endl;

        switch (move->getDialogue()) {
        case 0: cout << ""; break;
        case 1: cout << "Enemy's Defence is lowered" << endl; break;
        case 2: cout << "Enemy's Power is lowered" << endl; break;
        case 3: cout << this->name << "'s stats got boosted!" << endl; break;
        default: break;
        }
        cout << endl;

        this->setPower(this->getPower() + move->getPowerSelf());
        this->setDefence(this->getDefence() + move->getDefenceSelf());
    }
    else{
        cout << "Attack Misses.." << endl << endl;
    }
}
void pokemon::setName(string s){
    name = s;
}
string pokemon::getName(){

    return name;
}

void pokemon::setMove(int arrayIndex, int movenumber){

    moves[arrayIndex] = new attack(movenumber);

}

attack * pokemon::getMove(int i){
    return moves[i];
}
int pokemon::getnumber(){
    return numberInList;
}

void pokemon::setnumber(int i){
    numberInList = i;
}
string pokemon::getSprite(int s){
    return sprite[s];
}

void pokemon::setSprite(int s, string i){
    sprite[s] = i;
}

