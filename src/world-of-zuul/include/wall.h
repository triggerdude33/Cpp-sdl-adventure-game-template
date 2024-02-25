
#ifndef WALL_H
#define WALL_H

#include "entity.h"
#include <vector>

/**
    Entity class which describes an impassable wall
    or some other form of obstructed area.

 @author Matteus Berg
 @date 2023-10-27
*/
class Wall : public Entity{
public:
    using Entity::Entity;

    Wall(int row, int col);

    char utfRepresentation() override;
    void copyRGB(char* rgb) override;
    
};

#endif