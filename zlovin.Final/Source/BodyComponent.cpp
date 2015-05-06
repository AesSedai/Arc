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

void BodyComponent::Initialize(b2World* world, b2FixtureDef* shapefd, float x, float y, float a)
{
    //Intialize Body Definition
    bd.type = b2_dynamicBody;
    bd.position.Set(RW2PW(x),RW2PW(y));
    bd.angle = RW2PWAngle(a);

    //Create Body within Physics World
    body = world->CreateBody(&bd);  //Register Body with Physics World

    //Create Fixture within Body (links to Physics World)
    body->CreateFixture(shapefd); //Register fixture with physics world
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
