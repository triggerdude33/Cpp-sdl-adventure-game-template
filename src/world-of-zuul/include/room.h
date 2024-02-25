
#include "Matrix.h"
#include "entity.h"
#include <memory>
#include <vector>
#include <string.h>

#ifndef ROOM_H
#define ROOM_H

using namespace std;

/**
    class that contains room properties. Actual room content is
    not stored in this class

 @author Matteus Berg
 @date 2023-10-27
*/
class Room{
public:
    Room(int index, string m_description);

    /**
        compares two room indicies
        @return true if this room's index is identical to other index. Otherwise returns false
    */
    bool operator==(const Room& other);

    /**
        @param direction the direction to add the room. Must be north, west, east or south
        @param roomName the name of the room which this room exits to
        @throws std::invalid_argument if it receives an exit direction which is not
        north, west, east or south
    */
    void addExit(string direction, string roomName);

    /**
        @return the element index in the board_vector where this room's board is stored
    */
    int getIndex() const;

    /**
        @param dir the direction of the exit to get
        @throws std::invalid_argument if the requested exit is not north, west, east
        or south
    */
    string getExit(int dir) const;

    /**
        @return the description of this room
    */
    string getDescription();

private:
    int m_index;
    vector<string> m_exits;
    string m_description;
};

#endif