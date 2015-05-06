#include "Common.h"
#include "GraphicsDevice.h"
#include "Object.h"
#include "RenderComponent.h"
#include "BodyComponent.h"
#include "Texture.h"
#include "View.h"

RenderComponent::RenderComponent( std::shared_ptr<Object> owner ) : Component( owner )
{
    texture = nullptr;
    gDevice = nullptr;
}

RenderComponent::~RenderComponent() {}

bool RenderComponent::Initialize()
{
    return true;
}

void RenderComponent::Initialize( GraphicsDevice* gDevice, Texture* t )
{
    this->gDevice = gDevice;

    //Add RenderComponent to gDevice
    gDevice->AddRenderComponent( this );

    //Load the Art Asset
    texture = t;
}

void RenderComponent::Start() {}

void RenderComponent::Update() {}

void RenderComponent::Finish() {}

void RenderComponent::Draw( View* v )
{
    //Convert Physics World Position to Render World Position
    std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();

    //Extract position and angle
    b2Vec2 position = body->GetPosition();
    GAME_FLT angle = body->GetAngle();
    GAME_INT drawX = ( GAME_INT )( PW2RW( position.x ) - texture->getWidth() / 2.0f );
    GAME_INT drawY = ( GAME_INT )( PW2RW( position.y ) - texture->getHeight() / 2.0f );
    GAME_FLT drawAngle = PW2RWAngle( angle );

    //Render to the Screen
    texture->renderEx( gDevice->GetRenderer(), drawX, drawY, drawAngle, v, nullptr );
}

GAME_INT RenderComponent::GetWidth()
{
    return texture->getWidth();
}

GAME_INT RenderComponent::GetHeight()
{
    return texture->getHeight();
}
