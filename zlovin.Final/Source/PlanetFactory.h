#pragma once

#include <string>

#include "ObjectFactory.h"

class PlanetFactory: public ObjectFactory
{
public:
    PlanetFactory(void);
    ~PlanetFactory(void);

    //public methods
    std::shared_ptr<Object> Create(Game* g, tinyxml2::XMLNode* node, std::string name);
};
