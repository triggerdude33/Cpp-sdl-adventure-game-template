
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;


/**
    class that describes a entity which occupies a cell
    on a board

 @author Matteus Berg
 @date 2023-10-27
*/
class Entity{
public:
    Entity(int row, int col, string location);

    /**Request to move in a direction*/
    virtual void requestMove();
    virtual void requestMove(int direction);

    /**
        @return a single char which uniquely represents this type of entity
    */
    virtual char utfRepresentation();

    /**
        copies this entity's red green blue value into a 3 element char array
        @param rgb the 3-element char array to input this entity's RGB value into
    */
    virtual void copyRGB(char* rgb);
    
    // getters
    int getRow();
    int getCol();
    string getLocation();
    int getVelocity();

    // setters
    void setRow(int row);
    void setCol(int col);
    void setLocation(string loc);
    /**
        @throw std::invalid_argument if the given veolicty is invalid.
    */
    void setVelocity(int velocity);
    
protected:
    int m_row, m_col, m_velocity;
    string m_location;
};

#endif