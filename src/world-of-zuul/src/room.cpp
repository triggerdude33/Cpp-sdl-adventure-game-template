#include "room.h"
#include "properties.h"

#ifndef ROOM_CPP
#define ROOM_CPP

Room::Room(int index, string description) : 
    m_exits(vector<string>(4)),
    m_description(description),
    m_index(index)
{
}

void Room::addExit(string direction, string roomName){
    if(!strcmp(direction.data(), "north"))
        m_exits[NORTH] = roomName;
    else if(!strcmp(direction.data(), "west"))
        m_exits[WEST] = roomName;
    else if(!strcmp(direction.data(), "east"))
        m_exits[EAST] = roomName;
    else if(!strcmp(direction.data(), "south"))
        m_exits[SOUTH] = roomName;
    else{
        std::cerr << "Exit found '" << direction << "'" << std::endl;
        throw std::invalid_argument("Invalid direction given for exit!");
    }
}

bool Room::operator==(const Room& other){
    if(other.getIndex() == m_index) 
        return true;
    else 
        return false;
}

int Room::getIndex() const{
    return this->m_index;
}

string Room::getExit(int dir) const{
    if(m_exits.at(dir) == ""){
        cerr << "Error. Cannot exit in direction " << dir << std::endl;
        throw std::out_of_range("Invalid exit out of room");
    }

    return m_exits.at(dir);
}

string Room::getDescription(){
    return this->m_description;
}

#endif