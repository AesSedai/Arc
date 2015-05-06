#pragma once

//C++ Libraries
#include <iostream>
#include <map>
#include <memory>

//Dependencies
#include "SDL.h"
#include "Definitions.h"

class InputDevice
{
public:
    InputDevice(void);
    ~InputDevice(void);

    bool Initialize();
    void Update(SDL_Event* event);

    bool GetEvent(GAME_EVENT event);
    bool SetEvent(GAME_EVENT event, bool value);

private:

    std::map<GAME_INT, GAME_EVENT> event_map;
    std::map<GAME_EVENT, bool> events;
};
