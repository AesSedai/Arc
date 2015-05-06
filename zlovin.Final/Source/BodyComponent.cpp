#include"BodyComponent.h"
#include "Common.h"
#include "Component.h"
#include "Object.h"

BodyComponent::BodyComponent(std::shared_ptr<Object> owner) : Component(owner){}

BodyComponent::~BodyComponent(){}

bool BodyComponent::Initialize()
{
    return true;
}

void BodyComponent::Initialize(b2World* world, b2Shape* shape, float x, float y, float a, float w, float h, float d)
{
    //Intialize Body Definition
    bd.type = b2_dynamicBody;
    bd.position.Set(RW2PW(x),RW2PW(y));
    bd.angle = RW2PWAngle(a);

    //Create Body within Physics World
    body = world->CreateBody(&bd);  //Register Body with Physics World

    //Initialize Fixture Definition (shape, density, restitution)
    shapefd.shape = shape;
    shapefd.density = d;
    shapefd.friction = 0.5f;
    shapefd.restitution = 0.9f;

    //Create Fixture within Body (links to Physics World)
    body->CreateFixture(&shapefd); //Register fixture with physics world
}

void BodyComponent::Start(){}

void BodyComponent::Update(){}

void BodyComponent::Finish(){}

b2Vec2 BodyComponent::GetPosition(){
    return(body->GetPosition());
}

float BodyComponent::GetAngle()
{
    return(body->GetAngle());
}

b2Body* BodyComponent::GetBody()
{
    return(body);
}
