#include "PlayerBehaviorComponent.h"
#include "Object.h"
#include "BodyComponent.h"
#include "Common.h"
#include "InputDevice.h"

PlayerBehaviorComponent::PlayerBehaviorComponent(std::shared_ptr<Object> owner) : Component(owner){}

PlayerBehaviorComponent::~PlayerBehaviorComponent(void)
{
    if(iDevice) delete iDevice;
}

bool PlayerBehaviorComponent::Initialize()
{
    rotateAmount = RandomFloat(-3.0, 3.0);
    return true;
}

void PlayerBehaviorComponent::Start(void)
{
}

void PlayerBehaviorComponent::Update(void)
{
    std::shared_ptr<BodyComponent> bodyComponent = _owner->GetComponent<BodyComponent>();
    b2Body* body = bodyComponent->GetBody();

    if(iDevice->GetEvent(PLAYER_FORWARD))
    {
        b2Vec2 force = b2Vec2( cos(body->GetAngle()+PI/2.0)*-2.5, sin(body->GetAngle()+PI/2.0)*-2.5);
        body->ApplyForceToCenter(force);
    }
    else if(iDevice->GetEvent(PLAYER_BACKWARD))
    {
        b2Vec2 force = b2Vec2( cos(body->GetAngle()+PI/2.0)*2.5, sin(body->GetAngle()+PI/2.0)*2.5);
        body->ApplyForceToCenter(force);
    }

    if(iDevice->GetEvent(PLAYER_LEFT))
    {
        if(body->GetAngularVelocity() > -0.5f)
        {
            body->ApplyAngularImpulse(body->GetInertia() * -0.5f);
        }
    }
    else if(iDevice->GetEvent(PLAYER_RIGHT))
    {
        if(body->GetAngularVelocity() < 0.5f)
        {
            body->ApplyAngularImpulse(body->GetInertia() * 0.5f);
        }   
    }
    else
    {
        body->SetAngularVelocity(0.0f);
    }
}

void PlayerBehaviorComponent::Finish(void)
{
}

void PlayerBehaviorComponent::SetInputDevice(InputDevice* i)
{
    iDevice = i;
}
