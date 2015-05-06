#pragma once

#include "Component.h"
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

protected:
    float dt;
    float rotateAmount;
    InputDevice* iDevice;
};
