#include <iostream>
#include <cmath>
#include "cmr_player.h"
using namespace std;

Player::Player()
    : User_type()
{
    //initializes and allocates all memory
    dx = 0;
    dy = 0;
    fightopen = false;
    image.load("playerbe.png");

    rect = image.rect();
    resetState();
    party[0] = new pokemon(0);
    party[1] = new pokemon(1);
    party[2] = new pokemon(2);


}

Player::~Player(){
    //frees pokemon memory
    delete party[0];
    delete party[1];
    delete party[2];
}
//******************************************************* Virtual functions from user_type
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
