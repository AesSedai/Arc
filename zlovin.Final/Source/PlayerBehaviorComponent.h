#pragma once

#include "Component.h"
#include "Box2D/Box2D.h"

class View;
class Object;
class InputDevice;

class PlayerBehaviorComponent : public Component
{
public:
    PlayerBehaviorComponent(std::shared_ptr<Object>);
    ~PlayerBehaviorComponent();
    bool Initialize();
    void Start();
    void Update();
    void Finish();
    void SetInputDevice(InputDevice* i);
    void SetView(View* i);
    b2Vec2 GetPosition();

protected:
    float dt;
    float rotateAmount;
    InputDevice* iDevice;
    View* view;
};
