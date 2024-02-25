#include "properties.h"

#ifndef TERMINAL_ONLY
#include <SDL.h>
#endif

#include <iostream>
#include <fstream>
#include <algorithm>

#include <vector>
#include <ctime>
#include <memory>
#include <unordered_map>

#include "room.h"
#include "entity.h"
#include "player.h"
#include "wall.h"
#include "Matrix.h"

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

/**
    Class that constructs and keeps state of adventure game

    Stores all rooms inside a hashmap. Room name is key and Room class is value
    Stores all boards inside a shared_ptr vector. Each board corresponds to one room.
    Stores all entities inside a shared_ptr vector

    @author Matteus Berg
    @date   2023-10-27
*/
class GameManager{
public:
    GameManager(string inputLocation);

    // main functions
    
    /**
    @param inputLocation the location of the file to parse input from
    @throws std::runtime_error if it cannot find a file in inputLocation
    @throws std::invalid_argument if it parses a entity character from file which it doesn't recognize

    Each room contains and index (int) which links it with
    its corresponding board.
    Set "DEBUG" in properties.h to 1 to get debug messages of parsing
    input from file.
    */
    void parseRooms(string inputLocation);
    
    /**
        @param b the board which we would like to clear all non-wall entities from
    */
    void clearEntities(
        shared_ptr<Matrix<shared_ptr<Entity>>>& b
    );

    /**
        executes requested moves (if possible) for all entities inside of the "entities" vector.
        Additionally calls interact function if player entity requests to move into another entity

        Does not set any entities on the board. Only changes entites internal coordinates
        Assumes that all entities from entity vector are assigned to their boards

        @throws std::invalid_argument if an entity has set its velocity to an illegal value
    */
    void moveEntities();


    /**
        Checks if the player has moved outside the current room. If so,
        the function will update the current board shared_ptr and room
        pointer.

        @return true of room switch is made, otherwise false.
    */
    bool switchRoom();

    /**
        @param b the board to assign entities to
        @param r the board's corresponding room

        assigns all non-wall entities to a board
    */
    void assignEntities(
        shared_ptr<Matrix<shared_ptr<Entity>>>& b,
        Room* r
    );

    /**
        @param renderer the SDL renderer used for rendering
        @param b the board to render
    */

    void drawBoard(
#ifndef TERMINAL_ONLY
        SDL_Renderer * renderer,
#endif
        shared_ptr<Matrix<shared_ptr<Entity>>>& b
    );

private:
        // helper functions
    /**
        @param iep interacted entity pointer

        This is called when the player interacts with an entity. 
        The Entity type-specific behaviour is then executed
    */
    void interact(shared_ptr<Entity> iep);

    /**
        @return board for a specific entity
    */
    shared_ptr<Matrix<shared_ptr<Entity>>> getBoardForEntity(Entity& e);

public:
    // variables

    //rooms hashmap of rooms used to access all rooms
    unordered_map<string, Room> m_rooms; 

    // vector that owns all boards
    vector<shared_ptr<Matrix<shared_ptr<Entity>>>> m_board_vec;
    
    //the entity vector that owns all entities
    vector<shared_ptr<Entity>> m_entities;
    
    // current board
    shared_ptr<Matrix<shared_ptr<Entity>>> m_cb;
    
    // current room
    Room* m_cr;

    // player pointer
    Entity* m_p;
};

#endif