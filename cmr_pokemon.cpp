#include "cmr_pokemon.h"
#include "cmr_attack.h"

# include <iostream>
# include <fstream>
# include <iomanip>
#include <string>
#include <ctime>
#define GAP "        "
using namespace std;
//default constructor used to help in useful constructor
pokemon::pokemon(){
    //initialization and allocation
    health = 100;
    defence = 10;
    power = 10;
    name = "name";
    moves[0] = new attack ("n",0,0,0,0,0,0);
    moves[1] = new attack ("n",0,0,0,0,0,0);
    moves[2] = new attack ("n",0,0,0,0,0,0);
    moves[3] = new attack ("n",0,0,0,0,0,0);
    sprite[0] = "i.png"; // front view sprite
    sprite[1] = "i.png"; // back view sprite
}
//used constructor
pokemon::pokemon( int PokeNumber)
{
    //pulls initialization value based on number in pokedex array
    int index = PokeNumber;
    //opens pokedex file
    ifstream pokeDex;
    pokeDex.open("Pokedex.txt");
    if (pokeDex.fail()){
        cout << "unable to open pokedex" << endl;
        exit(1);
    }
    //takes in first value which is the number of pokemon in the list on the text file
    int numPoke = 0;
    pokeDex >> numPoke;
    //creates an array of pokemon pointers with the size of the number of pokemon that exist
    pokemon * Dex[numPoke];


    //cout << numPoke << "  " << Dex[0]->getName() << " " << Dex[0]->getHealth() << endl;

    //temporary variables
    int number;
    int h;
    int d;
    int p;
    string n;
    int move1, move2, move3,move4;
    string image_back;
    string image_front;

    int i =0;
    //reads from file for as long as another line can be, deposits data into initialiation array
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
    //closes file
    pokeDex.close();


    //sets the current object to the array indexed with the iniialization number
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
    //deletes the pokedex array that was read from file
    for(int k = 0 ; k < numPoke; k ++){
        delete Dex[k];
    }
}
//
pokemon::~pokemon(){
 \
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
    //sets a temp variable to arbitrary damage based on power and defence
    int totalDamage = ((float)(this->getPower()-p->getDefence())/100+1) * move->getDamage();
    //if statement with chance to miss target
    if (rand()%1000 < 650){
        //overloaded function to take damage
        *p - totalDamage;
        //sets new power
        p->setPower(p->getPower() + move->getPowerOp());
        //sets new defence
        p->setDefence(p->getDefence() + move->getDefenceOp());
        //prints the damage outcome of the move
        cout << GAP << getName() << " uses " << move->getname() << ". " << endl
             << GAP << "It hits " << p->getName() << " for " << totalDamage << " damage!" << endl;
        //prints custom dialogue based on moves initialization characteristics
        switch (move->getDialogue()) {
        case 0: cout << ""; break;
        case 1: cout << GAP << p->getName() <<"'s Defence is lowered" << endl; break;
        case 2: cout << GAP << p->getName() <<"'s Power is lowered" << endl; break;
        case 3: cout << GAP << this->name << "'s stats got boosted!" << endl; break;
        default: break;
        }
        cout << endl;
        //sets player values based on move
        this->setPower(this->getPower() + move->getPowerSelf());
        this->setDefence(this->getDefence() + move->getDefenceSelf());
    }
    else{
        cout << GAP << "Attack Misses.." << endl << endl;
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
void pokemon::operator-(const int i){
    this->setHealth(this->getHealth()-i);
}

