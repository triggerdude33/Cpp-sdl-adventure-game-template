#include <math.h>
#include "entity.h"
#include "properties.h"
#include <iostream>

#ifndef ENTITY_CPP
#define ENTITY_CPP

Entity::Entity(int row, int col, string location) 
        : m_row(row), 
        m_col(col),
        m_velocity(STATIONARY),
        m_location(location)
{}

void Entity::requestMove(){
    
}

void Entity::requestMove(int direction){

}

char Entity::utfRepresentation(){
    return ENTITY_UTF;
}

void Entity::copyRGB(char* rgb){
    rgb[0] = (char)ENTITY_COLOR;
    rgb[1] = (char)ENTITY_COLOR;
    rgb[2] = (char)ENTITY_COLOR;
}

int Entity::getRow(){
    return m_row;
}

int Entity::getCol(){
    return m_col;
}

int Entity::getVelocity(){
    return m_velocity;
}

void Entity::setRow(int row){
    m_row = row;
}

void Entity::setCol(int col){
    m_col = col;
}

void Entity::setLocation(string loc){
    m_location = loc;
}

void Entity::setVelocity(int velocity){
    if(velocity != STATIONARY && velocity != NORTH && velocity != WEST && velocity != EAST && velocity != SOUTH){
        cerr << "velocity " << velocity << std::endl;
        throw std::invalid_argument("Cannot set velocity to illegal value");
    }
    m_velocity = velocity;
}

string Entity::getLocation(){
    return m_location;
}

#endif