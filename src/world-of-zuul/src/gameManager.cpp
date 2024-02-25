#include "gameManager.h"

#ifndef GAME_MANAGER_CPP 
#define GAME_MANAGER_CPP

/*
Helper functions for main.cpp
*/

GameManager::GameManager(string inputLocation){
    // parse all rooms from input file
    parseRooms(inputLocation);

    // we begin in the "start" room
    m_cr = &m_rooms.find("start")->second;
    // shared pointer for the current board (m_cb) that should be displayed
    m_cb = m_board_vec.at(m_cr->getIndex());

    // print start room description
    std::cout << m_cr->getDescription() << std::endl;

    // create entities
    // OBS: Player must be pushed to entities vector first
    // TODO: Ta bort denna kod och få entities att parsas direkt från fil!
    m_entities.push_back(make_shared<Player>(Player(5, 2, "start", 3)));
    m_entities.push_back(make_shared<Entity>(Entity(5, 24, "borggarden")));
    m_p = m_entities.at(0).get();
}


/**
Each room contains and index (int) which links it with
its corresponding board.

Set "DEBUG" in properties.h to 1 to get debug messages of parsing
input from file.
*/
void GameManager::parseRooms(string inputLocation)
{
    // open file in input directory
    ifstream input(inputLocation);
    if(!input.is_open())
        throw std::runtime_error("Could not open room file!");

    // parse and create rooms
    while(!input.eof()){
        // buffer string which will take input from istream
        string buffer(999, '-');
        string type;

        // parse room properties
        // To get the underlying array of the string, we use .data()
        input.getline(buffer.data(), 99, ';');
        if(DEBUG) std::cout << "read characters: '" << input.gcount() << "'" << std::endl;
        type = buffer.substr(0, input.gcount()-1);
        // Debug code here
        if(DEBUG) std::cout << "'" << input.peek() << "'" << std::endl;
        if(DEBUG) std::cout << "'" << type << "'" << std::endl;
        

        if(!strcmp(type.data(), "Room")){
            string name;
            int room_size[2];
            string description;

            input.getline(buffer.data(), 99, ';');
            name = buffer.substr(0, input.gcount()-1);
            if(DEBUG) std::cout << "read characters: '" << input.gcount() << "'" << std::endl;
            if(DEBUG) std::cout << "name: '" << name << "'" << std::endl;
            input >> room_size[0];
            input >> room_size[1];
            input.get();
            input.getline(buffer.data(), 999, '\n');
            description = buffer.substr(0, input.gcount()-1);
            if(DEBUG) std::cout << room_size[0] << " " << room_size[1] << std::endl;
            
            // create Matrix and parse board
            Matrix<shared_ptr<Entity>> board(room_size[0], room_size[1]);
            char elem;
            int row = 0; int col = 0;
            while(input >> elem){
                if(DEBUG) std::cout << elem << " " << std::flush;
                switch(elem){
                    // TODO alt 2: Lägg till fler fall för entities här
                    case (int)EMPTY_UTF:
                        board(row,col) = nullptr;
                        break;
                    case (int)WALL_UTF:
                        board(row,col) = make_shared<Wall>(row, col);
                        break;
                    default:
                        cerr << "error in parsing board " << name <<  
                        ". Unable to intepret \""<< (char)elem << "\"" << endl;
                        throw std::invalid_argument("err");
                        break;
                }
                if(++col == room_size[1]){
                    col = 0;
                    row++;
                    if(DEBUG) std::cout << std::endl;
                }
                if(row == room_size[0]){
                    // get the last line break (\n)
                    input.get();
                    break;
                }
            }
            // add the newely parsed room to room hashmap and board vector
            m_board_vec.push_back(make_shared<Matrix<shared_ptr<Entity>>>(board));
            Room r = Room(m_board_vec.size()-1, description);
            m_rooms.insert({name, r});

            if(DEBUG) std::cout << "Finished parsing room'" << std::endl;

        }
        else if(!strcmp(type.data(), "Exit")){
            // add exit to room
            string from, dir, to;
            
            input.getline(buffer.data(), 99, ';');
            from = buffer.substr(0, input.gcount()-1);
            
            input.getline(buffer.data(), 99, ';');
            dir = buffer.substr(0, input.gcount()-1);
            
            input.getline(buffer.data(), 99, '\n');
            // if the end of file has been reached, we won't have read a \n character
            // and therefore we should read the exact amount of characters from input
            to = buffer.substr(0, input.eof() ? input.gcount() : input.gcount()-1);

            // We want to access the second element i.e the "value" in the key value pair.
            m_rooms.find(from)->second.addExit(dir, to);

            if(DEBUG) std::cout << "Finished parsing exit" << std::endl;
        }
        else{
            std::cerr << "Type parsed: '" << type << "'" << std::endl;
            throw std::invalid_argument("Expected 'Room' or 'Exit' type when parsing room input file");
        }
        // TODO alt 1: Lägg till en if-sats här för Entities

    }
    if(DEBUG) std::cout << "File parsing finished" << std::endl;
}


void GameManager::clearEntities(shared_ptr<Matrix<shared_ptr<Entity>>>& b)
{
    char color[3];
    int rows = (int)b->rows();
    int cols = (int)b->cols();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            // if shared_pointer owns an entity
            if(b->operator()(i, j).get() != nullptr){
                b->operator()(i, j).get()->copyRGB(color);
                // if its not a wall, shared_ptr releases its ownership of the entity
                if(color[0] != (char)WALL_COLOR || color[1] != (char)WALL_COLOR || color[2] != (char)WALL_COLOR)
                    b->operator()(i, j).reset();
            }
        }
    }
}


void GameManager::moveEntities()
{
    for(auto e = m_entities.begin(); e < m_entities.end(); e++){
        // get the entity velocity
        int velocity = e->get()->getVelocity();
        int row_velocity = 0;
        int col_velocity = 0;

        // see which direction entity wants to move
        switch(velocity){
            case -1:
                continue;
            case NORTH:
                row_velocity = -1;
                break;
            case WEST:
                col_velocity = -1;
                break;
            case EAST:
                col_velocity = 1;
                break;
            case SOUTH:
                row_velocity = 1;
                break;
            default:
                cerr << "velocity " << velocity << std::endl;
                throw std::invalid_argument("Illegal velocity in entity found in moveEntites function");
                break;
        }
        int requestedRow = e->get()->getRow() + row_velocity;
        int requestedCol = e->get()->getCol() + col_velocity;
        // find board that entity exists in
        shared_ptr<Matrix<shared_ptr<Entity>>> eb = getBoardForEntity(*e->get());
        // if it is the player
        if(e->get()->utfRepresentation() == PLAYER_UTF){
            // if the player is attempting to move to another room
            if(requestedRow < 0 || requestedCol < 0 || requestedRow > ((int)eb->rows()-1) || requestedCol > ((int)eb->cols()-1)){
                e->get()->setRow(e->get()->getRow() + row_velocity);
                e->get()->setCol(e->get()->getCol() + col_velocity);
                return; // return. Switch room will then register out of bounds player coordinates and switch room
            }
                
            // if the player wants to move to an empty cell
            else if(eb->operator()(requestedRow, requestedCol).get() == nullptr){
                e->get()->setRow(e->get()->getRow() + row_velocity);
                e->get()->setCol(e->get()->getCol() + col_velocity);
            }
            // else player interacts with entity
            else{
                if(DEBUG) cout << "Player interacts with entity" << endl;
                // calls interact function which decides what will happen depending on type of entity
                interact(eb->operator()(requestedRow, requestedCol));
            }
        }
        // else if it is an entity and it is requesting to move to an empty cell inside of the board
        else if(requestedRow < (int)eb->rows() && requestedCol < (int)eb->cols() && requestedRow >= 0 && requestedCol >= 0){
            if(eb->operator()(requestedRow, requestedCol).get() == nullptr){
                e->get()->setRow(e->get()->getRow() + row_velocity);
                e->get()->setCol(e->get()->getCol() + col_velocity);
            }
        }

        e->get()->setVelocity(STATIONARY);
    }
}


bool GameManager::switchRoom()
{
    bool roomSwitch = false;
    string newLocation;

    if((int)m_p->getRow() < 0){
        roomSwitch = true; 
        newLocation = m_cr->getExit(NORTH);
        m_cr = &m_rooms.find(newLocation)->second;
        m_cb = m_board_vec.at(m_cr->getIndex());
        m_p->setRow(m_cb->rows()-1);
        m_p->setCol(m_cb->cols()/2);
    }
    else if((int)m_p->getCol() < 0){ 
        roomSwitch = true;
        newLocation = m_cr->getExit(WEST);
        m_cr = &m_rooms.find(newLocation)->second;
        m_cb = m_board_vec.at(m_cr->getIndex());
        m_p->setRow(m_cb->rows()/2);
        m_p->setCol(m_cb->cols()-1);
    }
    else if((int)m_p->getCol() > (int)m_cb->cols()-1){
        roomSwitch = true;
        newLocation = m_cr->getExit(EAST); 
        m_cr = &m_rooms.find(newLocation)->second;
        m_cb = m_board_vec.at(m_cr->getIndex());
        m_p->setRow(m_cb->rows()/2);
        m_p->setCol(0);
    }
    else if((int)m_p->getRow() > (int)m_cb->rows()-1){ 
        roomSwitch = true;
        newLocation = m_cr->getExit(SOUTH);
        m_cr = &m_rooms.find(newLocation)->second;
        m_cb = m_board_vec.at(m_cr->getIndex());
        m_p->setRow(0);
        m_p->setCol(m_cb->cols()/2);
        
    }

    if(roomSwitch){
        if(DEBUG) std::cout << "Room switch done" << std::endl;
        m_p->setLocation(newLocation);

        return true;
    }

    return false;
}

void GameManager::assignEntities(
    shared_ptr<Matrix<shared_ptr<Entity>>>& b,
    Room* r)
{
    for(auto e = m_entities.begin(); e < m_entities.end(); e++){
        // if the entity's room is the same as the board's room
        if(m_rooms.find(e->get()->getLocation())->second == *r){
            b->operator()(e->get()->getRow(), e->get()->getCol()) = *e;
        }
    }
}

void GameManager::drawBoard(
#ifndef TERMINAL_ONLY
    SDL_Renderer * renderer,
#endif
    shared_ptr<Matrix<shared_ptr<Entity>>>& b)
{
    int rows = (int)b->rows();
    int cols = (int)b->cols();
#ifndef TERMINAL_ONLY
    SDL_Rect cell;
    cell.w = SCREEN_WIDTH / cols;
    cell.h = SCREEN_HEIGHT / rows;
    char color[3];
#endif

#ifndef TERMINAL_ONLY
    if(DEBUG) std::cout << "Start drawing board" << std::endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cell.x = (int)((double)j/cols * SCREEN_WIDTH);
            cell.y = (int)((double)i/rows * SCREEN_HEIGHT);
            if(DEBUG) cout << "drawing cell with coordinates: " << "(" << cell.x << ", " << cell.y << ")" << std::endl;
            // by default has black color
            color[0] = (char)0x0; color[1] = (char)0x0; color[2] = (char)0x0; 
            // if the cell is not empty, draw the color of the entity
            // that occupies that cell
            if(b->operator()(i, j).get() != nullptr){
                b->operator()(i, j).get()->copyRGB(color);
            }

            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 0xFF);
            SDL_RenderFillRect(renderer, &cell);
        }
    }
    // Update screen
    SDL_RenderPresent(renderer);
#else
    if(DEBUG) std::cout << "Start printing board" << std::endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(DEBUG) cout << "printing cell with coordinates: " << "(" << rows << ", " << cols << ")" << std::endl;
            // by default is empty
            char c = EMPTY_UTF;
            // if the cell is not empty, print representation of the entity
            // that occupies that cell
            if(b->operator()(i, j).get() != nullptr){
                c = b->operator()(i, j).get()->utfRepresentation();
            }

            std::cout << c << std::flush;
        }
        std::cout << std::endl;
    }
#endif
}

void GameManager::interact(
    shared_ptr<Entity> iep
)
{
    int entityType = (int)iep.get()->utfRepresentation();

    // TODO: Lägg till fler fall för andra typer av entities!
    switch(entityType){
        case ((int)WALL_UTF):
            std::cout << "You bumped your head into a wall. Ow, That hurt!" << std::endl;
            break;
        case ((int)ENTITY_UTF):
            std::cout << "You bumped into a gorilla. It stares at you intently. It then gives you a banana" << std::endl;
            break;
        default:
            std::cout << "You stare into some unknown void. After a while, you notice the void staring back" << std::endl;
            break;
    }
}

shared_ptr<Matrix<shared_ptr<Entity>>> GameManager::getBoardForEntity(Entity& e){
    return m_board_vec.at(m_rooms.find(e.getLocation())->second.getIndex());
}

#endif