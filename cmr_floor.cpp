#include "cmr_floor.h"
#include <iostream>
floor::floor(int x, int y)
{
    //location and image initialization
    image.load("dirt.png");
    rect = image.rect();
    rect.translate(x,y);
}
floor::~floor(){}

QRect floor::getRect(){
    return rect;
}
void floor::setRect(QRect r){
    rect = r;
}

QImage & floor::getImage(){
    return image;
}
