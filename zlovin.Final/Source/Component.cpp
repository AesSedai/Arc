#include "Object.h"
#include "Component.h"

Component::Component(std::shared_ptr<Object> owner) : _owner(owner){}

Component::~Component(){}

void Component::OwnerDestroyed()
{
    Finish();
    _owner.reset();
}

std::shared_ptr<Object> Component::GetOwner()
{
    return(_owner);
}
