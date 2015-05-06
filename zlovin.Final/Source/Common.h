/*
* Author:   Zach Lovin
*           UALR
*
* Date:     April 12, 2015
*
* File:     Common.h (Arc)
*
* Purpose:  This file is a catch-all header where common
*           functions can be placed to be easily reused
*           in various classes.
*/

#pragma once

//Dependencies
#include "Definitions.h"
#include "stdlib.h"

//========================================
//Box2D Functions
//========================================
const GAME_FLT fPRV = 10.0f;

const GAME_FLT R_TO_D = 180.0f / PI;

const GAME_FLT D_TO_R = PI / 180.0f;

inline GAME_FLT PW2RW (GAME_FLT x) {
    return x * fPRV;
}

inline GAME_FLT RW2PW (GAME_FLT x) {
    return x / fPRV;
}

inline GAME_FLT RW2PW (GAME_INT x) {
    return (GAME_FLT) x / fPRV;
}

inline GAME_FLT RW2PWAngle (GAME_FLT x) {
    return ( (GAME_FLT) x * D_TO_R);   //degrees to radians
}

inline GAME_FLT PW2RWAngle (GAME_FLT x) {
    return ( (GAME_FLT) x * R_TO_D);   //radians to degrees
}

inline GAME_FLT RandomFloat(GAME_FLT a, GAME_FLT b) {
    GAME_FLT random = ((GAME_FLT) rand()) / (GAME_FLT) RAND_MAX;
    GAME_FLT diff = b - a;
    GAME_FLT r = random * diff;
    return a + r;
}
