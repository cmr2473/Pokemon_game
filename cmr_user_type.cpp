#include <iostream>
#include <cmath>
#include "cmr_user_type.h"
using namespace std;
// default user initializations and alloacations
User_type::User_type()
{

    fightopen = false;
    image.load("playerbe.png");

    rect = image.rect();

    party[0] = new pokemon(0);
    party[1] = new pokemon(1);
    party[2] = new pokemon(2);


}

User_type::~User_type(){
    //frees memory from pokemon
    delete party[0];
    delete party[1];
    delete party[2];
}

void User_type::setDx(int x){
    Q_UNUSED(x);
}

void User_type::setDy(int y){
    Q_UNUSED(y);
}
int User_type::getDx(){
    return dx;
}
int User_type::getDy(){
    return dy;
}
void User_type::move(){
}

void User_type::resetState(){
}

QRect User_type:: getRect(){
    return rect;
}

QImage & User_type::getImage(){
    return image;
}

bool User_type::getFightOpen(){
    return fightopen;
}

void User_type::setFightOpen(bool l){
    fightopen = l;
}

pokemon* User_type::getPokemon(int i){
    return party[i];
}
int User_type::getPartySize(){
    return partySize;
}
void User_type::print(){
    cout << "Party: " << endl;
    for(int k =0; k < partySize ; k++){
        cout << party[k]->getName() << " " << party[k]->getHealth() << endl;
    }
}
