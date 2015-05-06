#pragma once

//Dependencies
#include "Box2D/Box2D.h"
#include "Component.h"

//Forward Declarations
class Object;

class BodyComponent : public Component
{
public:

    BodyComponent(std::shared_ptr<Object>);
    ~BodyComponent();
    bool Initialize();
    void Initialize(b2World* world, b2FixtureDef* shape, float x, float y, float a);

    void Start();
    void Update();
    void Finish();

    b2Vec2 GetPosition();
    float GetAngle();

    b2Body* GetBody();

protected:

    //Box2D Physics Components
    b2BodyDef bd;
    b2Body* body;
};
