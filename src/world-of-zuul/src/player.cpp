#include <math.h>
#include "player.h"
#include "properties.h"
#include <iostream>

#ifndef PLAYER_CPP
#define PLAYER_CPP

Player::Player(int row, int col, string location, int hp) 
        : Entity(row, col, location)
        , m_hp(hp)
{}

char Player::utfRepresentation(){
    return PLAYER_UTF;
}

void Player::copyRGB(char* rgb){
    rgb[0] = (char)PLAYER_COLOR_1;
    rgb[1] = (char)PLAYER_COLOR_2;
    rgb[2] = (char)PLAYER_COLOR_3;
}


void Player::requestMove(int direction){
    // change player velocity. Movement is then handled by gameManager which will move the player.
    switch(direction){
        case NORTH:
            m_velocity = NORTH; 
            break;
        case WEST:
            m_velocity = WEST;
            break;
        case EAST:
            m_velocity = EAST;
            break;
        case SOUTH:
            m_velocity = SOUTH;
            break;
        default:
            break;
    }
}


#endif