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
    void Initialize(b2World* world, b2Shape*, float x, float y, float a, float w, float h, float d);

    void Start();
    void Update();
    void Finish();

    b2Vec2 GetPosition();
    float GetAngle();

    b2Body* GetBody();

protected:

    //Box2D Physics Components
    b2BodyDef bd;
    b2PolygonShape shape;
    b2FixtureDef shapefd;
    b2Body* body;
};
