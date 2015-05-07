#pragma once

//C++ Libraries
#include <map>
#include <string>
#include <memory>
#include <iostream>

//Dependencies
#include "Box2D/Box2D.h"
#include "Common.h"

class BodyAssetLibrary
{
public:
    BodyAssetLibrary(void);
    ~BodyAssetLibrary(void);

    //public methods
    bool Initialize(std::string path);
    b2FixtureDef* Create(std::string);

private:
    std::map<std::string, fixture_params*> library;
};
