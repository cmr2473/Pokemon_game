#include <iostream>
#include "cmr_wall.h"

wall::wall(int x, int y)
{
    image.load("upwall.png");
    rect = image.rect();
    rect.translate(x,y);

}
wall::wall(int x, int y, int k){
    Q_UNUSED(k);
    image.load("sidewall.png");
    rect = image.rect();
    rect.translate(x,y);
}

wall::~wall() {


}

QRect wall::getRect(){
    return rect;
}
void wall::setRect(QRect r){
    rect = r;
}

QImage & wall::getImage(){
    return image;
}

