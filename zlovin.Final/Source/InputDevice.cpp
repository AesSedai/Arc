#include "InputDevice.h"

InputDevice::InputDevice(void)
{
}

InputDevice::~InputDevice(void)
{
}

bool InputDevice::Initialize()
{
    if(SDL_WasInit(SDL_INIT_EVENTS)==0)
    {
        printf( "SDL could not initialize Events in InputDevice! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_LEFT, GAME_LEFT));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_RIGHT, GAME_RIGHT));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_UP, GAME_UP));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_DOWN, GAME_DOWN));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_a, PLAYER_LEFT));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_d, PLAYER_RIGHT));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_w, PLAYER_FORWARD));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_s, PLAYER_BACKWARD));
    event_map.insert(std::pair<GAME_INT, GAME_EVENT>(SDLK_SPACE, FIRE));

    for(std::map<GAME_INT, GAME_EVENT>::iterator it = event_map.begin(); it != event_map.end(); ++it)
    {
        events.insert(std::pair<GAME_EVENT, bool>(it->second, false));
    }

    return true;
}

void InputDevice::Update(SDL_Event* event)
{
    try
    {
        if(event->type == SDL_KEYDOWN) events.at(event_map[event->key.keysym.sym]) = true;
        if(event->type == SDL_KEYUP) events.at(event_map[event->key.keysym.sym]) = false;
    }
    catch(const std::out_of_range& oor)
    {
        oor;
        //Just here for posterity's sake. Don't need anyone trying to overflow a map because of [] behavior.
    }
}

bool InputDevice::GetEvent(GAME_EVENT event)
{
    return events[event];
}

bool InputDevice::SetEvent(GAME_EVENT event, bool value)
{
    try
    {
        events.at(event) = value;
        return true;
    }
    catch(const std::out_of_range& oor)
    {
        oor;
        return false;
        //Just here for posterity's sake. Don't need anyone trying to overflow a map because of [] behavior.
    }
}
