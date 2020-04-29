#include "cmr_grass.h"
//inherits from floor, changes image loaded
grass::grass(int x, int y) : floor(x,y)
{
    image.load("grass1.png");
}

