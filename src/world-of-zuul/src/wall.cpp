#include "wall.h"
#include "properties.h"
#include <iostream>

#ifndef WALL_CPP
#define WALL_CPP

Wall::Wall(int row, int col) 
        : Entity(row, col, "")
{}

char Wall::utfRepresentation(){
    return WALL_UTF;
}

void Wall::copyRGB(char* rgb){
    rgb[0] = (char)WALL_COLOR;
    rgb[1] = (char)WALL_COLOR;
    rgb[2] = (char)WALL_COLOR;
}

#endif