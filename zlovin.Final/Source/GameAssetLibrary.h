#pragma once

//C++ Libraries
#include <map>
#include <string>
#include <memory>

//Forward Declarations
class ObjectFactory;

class GameAssetLibrary
{
public:
    GameAssetLibrary(void);
    ~GameAssetLibrary(void);

    //public methods
    ObjectFactory* Search(std::string string);
    bool Initialize(void);

private:
    std::map<std::string, ObjectFactory*> library;
};
