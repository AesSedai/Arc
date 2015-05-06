/*
* Author:   Zach Lovin
*           UALR
*
* Date:     April 12, 2015
*
* File:     Definitions.h (Arc)
*
* Purpose:  This is a standard type redefinitions header that allows
*           for flexibility in programming should design parameters change.
*           Ideally, every SDL2 specific type would be renamed allowing
*           the code to be decoupled from any specific Media Library.
*/

#pragma once

//Basic Types
typedef unsigned int    Uint32;
typedef float           GAME_FLT;
typedef Uint32          GAME_INT;

typedef struct GAME_VEC
{
    GAME_FLT x;
    GAME_FLT y;
} GAME_VEC;

//Event Types
enum GAME_EVENT {
    GAME_NA,
    GAME_UP,
    GAME_DOWN,
    GAME_LEFT,
    GAME_RIGHT,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_FORWARD,
    PLAYER_BACKWARD,
    FIRE
};

//Constants
const GAME_FLT PI = 3.14159f;
