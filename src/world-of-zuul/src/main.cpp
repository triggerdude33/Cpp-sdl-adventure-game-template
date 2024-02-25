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
#include "gameManager.h"

using namespace std;

// TODO: Lägg till .cpp och .h filer för andra entities
// TODO: Lägg till en klass som ärver från flera klasser

int main()
{
#ifndef TERMINAL_ONLY

    // Initialisera SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        std::cout << "SDL can not disable compositor bypass!" << std::endl;
        return 0;
    }
#endif

    // Skapa fönster
    SDL_Window *window = SDL_CreateWindow("Basic C++ SDL project",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        std::cout << "Window could not be created!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        // Skapa renderare
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            std::cout << "Renderer could not be created!" << std::endl
                      << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        else
        {
#endif
            // Event loop exit flag
            bool quit = false;

            // create game manager
            GameManager manager(INPUT_DIR);

            // Event loop
            while(!quit)
            {
                if(DEBUG) std::cout << "player coordinates: (" << manager.m_p->getRow() << ", " << manager.m_p->getCol() << ")" << std::endl;

#ifndef TERMINAL_ONLY

                SDL_Event event;

                /* Poll for event */
                while( SDL_PollEvent( &event )){    
                    switch(event.type){
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_KEYUP:
                            break;
                        case SDL_KEYDOWN:
                            if(DEBUG) std::cout << "key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                            // arrow keys change player velocity. This is then handled by main which will move the player.
                            switch(event.key.keysym.sym){
                                case SDLK_w:
                                    manager.m_p->requestMove(NORTH);
                                    break;
                                case SDLK_a:
                                    manager.m_p->requestMove(WEST);
                                    break;
                                case SDLK_d:
                                    manager.m_p->requestMove(EAST);
                                    break;
                                case SDLK_s:
                                    manager.m_p->requestMove(SOUTH);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                }

                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(renderer);
#else           
                // parse input from terminal for movement if SDL is not used
                char c;
                int direction;
                std::cout << "> ";
                std::cin >> c;
                switch((int)c){
                    case (int)'w':
                        direction = NORTH;break;
                    case (int)'a':
                        direction = WEST;break;
                    case (int)'d':
                        direction = EAST;break;
                    case (int)'s':
                        direction = SOUTH;break;
                    case (int)'q':
                        quit = true;break;
                    default:
                        std::cerr << "Illegal input from user!" << std::endl;
                        throw std::invalid_argument("err");
                }
                manager.m_p->requestMove(direction);
                std::cout << std::endl;

#endif 
                // move (if possible) all entities that request to be moved
                manager.moveEntities();

                // clear non-wall entities from current board
                manager.clearEntities(manager.m_cb);

                // check if a room switch should be done
                // if it should be done: Switch room
                if(manager.switchRoom()){
                    // player arrives in new room. Print room description
                    std::cout << manager.m_cr->getDescription() << std::endl;
                }

                // assign non-wall entities to current board
                manager.assignEntities(manager.m_cb, manager.m_cr);

                // draw current board
                manager.drawBoard(
#ifndef TERMINAL_ONLY
                    renderer, 
#endif
                    manager.m_cb);

            }
#ifndef TERMINAL_ONLY
            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL
    SDL_Quit();

#endif

    return 0;
}
