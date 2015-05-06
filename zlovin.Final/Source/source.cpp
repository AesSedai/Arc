/*
* Author:   Zach Lovin
*           UALR
*
* Date:     April 12, 2015
*
* File:     Source.cpp
*
* Purpose:  This is the entry point to Arc
*/

// C++ Libraries
#include <iostream>
#include <ctime>
#include <memory>

// Media Libraries
#include "SDL.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"

// Miscellaneous
#include "Definitions.h"
#include "Common.h"
#include "Game.h"

int main( int argc, char *argv[] ) {
    argc;
    argv;

    //========================================
    // Initialize the random number generator
    //========================================
    srand( ( unsigned int )time( nullptr ) );

    //========================================
    // Base Game Constants
    //========================================
    GAME_INT SCREEN_WIDTH = 800;
    GAME_INT SCREEN_HEIGHT = 600;
    GAME_INT GAME_FPS = 100;
    GAME_FLT DT = 1.0f / 50.0f;

    //========================================
    // Initialize SDL
    //========================================
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "SDL could not initialize in Source! SDL_Error: %s\n",
                SDL_GetError() );
        std::cin.ignore();
        exit( 1 );
    }

    //========================================
    // Construct Graphical Device
    //========================================
    GraphicsDevice *gDevice = new GraphicsDevice( SCREEN_WIDTH, SCREEN_HEIGHT );
    if ( !gDevice->Initialize( true ) ) {
        printf( "Graphics Device could not initialize!\n" );
        std::cin.ignore();
        exit( 1 );
    }

    std::cout << "gDevice initialized" << std::endl;

    //========================================
    // Construct Event System
    //========================================
    if ( SDL_WasInit( SDL_INIT_EVENTS ) == 0 ) {
        printf( "SDL Event could not initialize in Source! SDL_Error: %s\n",
                SDL_GetError() );
        std::cin.ignore();
        exit( 1 );
    }
    SDL_Event *event = new SDL_Event();

    std::cout << "events initialized" << std::endl;

    //========================================
    // Construct Input Device
    //========================================
    InputDevice *iDevice = new InputDevice();
    if ( !iDevice->Initialize() ) {
        printf( "Input Device could not initialize!\n" );
        std::cin.ignore();
        exit( 1 );
    }

    std::cout << "iDevice initialized" << std::endl;

    //========================================
    // Construct Game
    //========================================
    Game *game = new Game();
    if ( !game->Initialize( gDevice, iDevice, GAME_FPS, DT ) ) {
        printf( "Game could not Initialize!\n" );
        std::cin.ignore();
        exit( 1 );
    }

    std::cout << "game initialized" << std::endl;

    //========================================
    //Load Level
    //========================================
    game->Reset();
    std::string levelConfigFile = "./Assets/Config/level.xml";
    if ( !game->LoadLevel( levelConfigFile ) )
    {
        std::cout << "Game could not load level: " << levelConfigFile <<
                  std::endl;
        exit( 1 );
    }

    //========================================
    // Main Game Loop
    //========================================
    bool quit = false;

    // While the user hasn't quit
    while ( !quit ) {
        // Check for Event
        while ( SDL_PollEvent( event ) ) {
            switch ( event->type ) {
            case SDL_QUIT: {
                quit = true;
                break;
            }
            case SDL_KEYDOWN: {
                // Update the Input Device with the Event
                iDevice->Update( event );
            }
            case SDL_KEYUP: {
                // Update the Input Device with the Event
                iDevice->Update( event );
            }
            }

            // Execute the Game
            
        }
        game->Run();
    }

    std::cin.ignore();
    return 0;
}
