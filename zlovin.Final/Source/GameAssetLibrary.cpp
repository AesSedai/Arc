#include "GameAssetLibrary.h"
#include "tinyxml2.h"
//#include "CarrierFactory.h"
//#include "InfantryFactory.h"
#include "PlayerFactory.h"

GameAssetLibrary::GameAssetLibrary(void)
{
}

GameAssetLibrary::~GameAssetLibrary(void)
{
}

bool GameAssetLibrary::Initialize()
{
    //library.insert(std::pair<std::string, ObjectFactory*>("Carrier", new CarrierFactory()));
    //library.insert(std::pair<std::string, ObjectFactory*>("Infantry", new InfantryFactory()));
    library.insert(std::pair<std::string, ObjectFactory*>("Player", new PlayerFactory()));
    return true;
}

ObjectFactory* GameAssetLibrary::Search(std::string string)
{
    std::map<std::string, ObjectFactory*>::iterator it = library.find(string);
    if(it != library.end())
    {
        return it->second;
    }
    return nullptr;
}
