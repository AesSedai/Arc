#pragma once

#include <memory>
#include <string>

#include "tinyxml2.h"

class Game;
class Object;

class ObjectFactory
{
public:
    ObjectFactory(void);
    ~ObjectFactory(void);

    //public methods
    virtual std::shared_ptr<Object> Create(Game* g, tinyxml2::XMLNode* node, std::string name)=0;
};
