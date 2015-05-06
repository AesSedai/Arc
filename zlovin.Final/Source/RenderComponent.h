#pragma once

//C++ Libraries
#include <iostream>

//Dependencies
#include "Component.h"
#include "Definitions.h"

//Forward Declarations
class Object;
class GraphicsDevice;
class Texture;
class View;

class RenderComponent : public Component
{
public:
    RenderComponent( std::shared_ptr<Object> );
    ~RenderComponent();
    bool Initialize();
    void Initialize( GraphicsDevice* gDevice, Texture* t );
    void Start();
    void Update();
    void Finish();
    void Draw( View* v );
    void Present();

    GAME_INT GetWidth();
    GAME_INT GetHeight();

protected:
    Texture* texture;
    GraphicsDevice* gDevice;
};
