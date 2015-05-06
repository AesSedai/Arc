#pragma once

//C++ Libraries
#include <map>
#include <string>

//Forward Declarations
class GraphicsDevice;
class Texture;
class View;

class ArtAssetLibrary
{
public:
    ArtAssetLibrary(void);
    ~ArtAssetLibrary(void);

    //public methods
    bool Initialize(GraphicsDevice* gDevice, std::string path);
    Texture* Search(std::string string);

private:
    GraphicsDevice* gDevice;
    std::map<std::string, Texture*> library;
};
