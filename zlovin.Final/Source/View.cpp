#include "View.h"
#include "InputDevice.h"
#include "Common.h"

View::View(void)
{
}

View::~View(void)
{
}

//GAME_FLT values correspond to the initial x- and y-coordinates of the View object
bool View::Initialize(InputDevice* iDevice, GAME_FLT px, GAME_FLT py)
{
    if(SDL_WasInit(SDL_INIT_EVENTS)==0)
    {
        printf( "SDL could not initialize Events in View! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    std::cout << "events was initialized." << std::endl;

    this->iDevice = iDevice;

    std::cout << "iDevice stored." << std::endl;

    position.x = px;
    position.y = py;

    return true;
}

GAME_VEC View::getPosition()
{
    return position;
}

//The view responds to GAME_EVENTs. Initially the current GAME_EVENT is requested from the InputDevice.
//The View then responds to keyboard events by shifting its position in accordance with the events.
void View::Update(GAME_FLT gameTime)
{
    gameTime;
    //if(iDevice->GetEvent(GAME_UP)) position.y -= 1.0;
    //if(iDevice->GetEvent(GAME_DOWN)) position.y += 1.0;
    //if(iDevice->GetEvent(GAME_LEFT)) position.x -= 1.0;
    //if(iDevice->GetEvent(GAME_RIGHT)) position.x += 1.0;
}

void View::setPosition(b2Vec2 p)
{
    position.x = PW2RW(p.x)-400;
    position.y = PW2RW(p.y)-300;
}