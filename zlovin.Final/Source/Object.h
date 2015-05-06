#pragma once

//C++ Libraries
#include <memory>
#include <iostream>
#include <vector>

//Forward Declarations
class Component;

class Object : public std::enable_shared_from_this<Object>
{
public:
    Object();
    ~Object();
    bool Initialize();
    void AddComponent(std::shared_ptr<Component> component);
    void Update();

    template<class T>
    std::shared_ptr<T> GetComponent()
    {
        for(auto comp : components)
        {
            std::shared_ptr<T> target;
            if((target = std::dynamic_pointer_cast<T>(comp)))
            {
                return(target);
            }
        }

        //Return nullptr;
        return(std::shared_ptr<T>());
    }

protected:
    std::vector<std::shared_ptr<Component>> components;
    bool initialized;
};
