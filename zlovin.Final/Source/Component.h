#pragma once

//C++ Libraries
#include <memory>

//Forward Declarations
class Object;

class Component
{
public:
    Component(std::shared_ptr<Object> owner);
    ~Component();

    virtual bool Initialize()=0;
    virtual void Start()=0;
    virtual void Update()=0;
    virtual void Finish()=0;

    void OwnerDestroyed();
    std::shared_ptr<Object> GetOwner();

protected:
    std::shared_ptr<Object> _owner;
};
