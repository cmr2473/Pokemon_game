#include <iostream>
#include <cmath>
#include "cmr_player.h"
using namespace std;

Player::Player()
{
    dx = 0;
    dy = 0;
    fightopen = false;
    image.load("playerbe.png");

    rect = image.rect();
    resetState();
    party[0] = new pokemon(0);
    party[1] = new pokemon(1);
    party[2] = new pokemon(2);
    cout << "Party: " << endl;
    for(int k =0; k < partySize ; k++){
        cout << party[k]->getName() << " " << party[k]->getHealth() << endl;
    }

}

Player::~Player(){
    delete party[0];
}

void Player::setDx(int x){
    dx = x;
}

void Player::setDy(int y){
    dy = y;
}
int Player::getDx(){
    return dx;
}
int Player::getDy(){
    return dy;
}
void Player::move(){

    int x = rect.x() + dx;
    int y = rect.y() + dy;
    rect.moveTo(x, y);

}

void Player::resetState(){
    rect.moveTo(INITIAL_X, INITIAL_Y);
}

QRect Player:: getRect(){
    return rect;
}

QImage & Player::getImage(){
    return image;
}

bool Player::getFightOpen(){
    return fightopen;
}

void Player::setFightOpen(bool l){
    fightopen = l;
}

pokemon* Player::getPokemon(int i){
    return party[i];
}
int Player::getPartySize(){
    return partySize;
}
