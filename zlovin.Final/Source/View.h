#pragma once

//C++ Libraries
#include <iostream>
#include <memory>

//Dependencies
#include "Definitions.h"

//Forward Declarations
class InputDevice;

class View
{
public:
    View(void);
    ~View(void);

    //public methods
    bool Initialize(InputDevice* iDevice, GAME_FLT px, GAME_FLT py); //GAME_FLT values correspond to the initial x- and y-coordinates of the View object
    void Update(GAME_FLT gameTime); //The view responds to GAME_EVENTs. Initially the current GAME_EVENT is requested from the InputDevice.
    //The View then responds to keyboard events by shifting its position in accordance with the events.
    GAME_VEC getPosition(void);

private:
    InputDevice* iDevice;
    GAME_VEC position;
};
