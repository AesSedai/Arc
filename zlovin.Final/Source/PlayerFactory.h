#pragma once

#include <string>

#include "ObjectFactory.h"

class PlayerFactory: public ObjectFactory
{
public:
    PlayerFactory(void);
    ~PlayerFactory(void);

    //public methods
    std::shared_ptr<Object> Create(Game* g, tinyxml2::XMLNode* node, std::string name);
};
