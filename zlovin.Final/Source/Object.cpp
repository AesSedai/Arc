#include "Object.h"
#include "Component.h"

Object::Object()
{
    initialized = false;
}

Object::~Object()
{
    for(auto comp: components)
    {
        comp->OwnerDestroyed();
        comp->~Component();
    }

    while(!components.empty()) components.pop_back();

    //components.clear();
}

bool Object::Initialize()
{
    //Call the start method
    if(!initialized)
    {
        for(auto comp : components)
        {
            comp->Start();
        }
        initialized = true;
    }

    return(initialized);
}

void Object::Update()
{
    for(auto comp : components)
    {
        comp->Update();
    }
}

void Object::AddComponent(std::shared_ptr<Component> component)
{
    components.push_back(component);
}
