#pragma once

//C++ Libraries
#include <vector>
#include <iostream>

//Dependencies
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

//Forward Declarations
class RenderComponent;
class View;

class GraphicsDevice
{
public:

    //Constructors and Destructors
    GraphicsDevice( Uint32, Uint32 );
    ~GraphicsDevice();

    //Accessors
    void AddRenderComponent( RenderComponent* );
    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();

    //Startup and Shutdown
    bool Initialize( bool );
    bool ShutDown();
    void SetView( View* v );

    //Rendering functions
    void Begin();
    void Draw();
    void Present();

    //non-copyable, give back *this if you want it
    GraphicsDevice& operator=( const GraphicsDevice& ) {return *this;}

private:

    View* view;

    //Parameters
    const Uint32 SCREEN_WIDTH;
    const Uint32 SCREEN_HEIGHT;

    //Window(s) to display graphics
    SDL_Window* screen;
    SDL_Renderer* renderer;

    //Renderers
    std::vector<RenderComponent*> renderComponents;
};
