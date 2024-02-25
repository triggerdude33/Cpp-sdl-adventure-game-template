
#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <vector>

/**
Entity class that is controlled by  the player

 @author Matteus Berg
 @date 2023-10-27
*/
class Player : public Entity{
public:
    using Entity::Entity;

    Player(int row, int col, string location, int hp);

    char utfRepresentation() override;
    void copyRGB(char* rgb) override;

    void requestMove(int direction) override;

protected:
    int m_hp;
    
};

#endif