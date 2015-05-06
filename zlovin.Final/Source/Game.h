#pragma once

//C++ Libraries
#include <vector>
#include <stdlib.h>
#include <string>
#include <memory>

//Media Library Wrappers
#include "Box2D/Box2D.h"

//Definitions
#include "Definitions.h"

class GraphicsDevice;
class InputDevice;
class Object;
class GameAssetLibrary;
class ArtAssetLibrary;
class BodyAssetLibrary;
class View;
class Timer;

class Game
{
public:
    Game(void);
    ~Game(void);

    //public methods
    bool Initialize(GraphicsDevice* gDevice, InputDevice* iDevice, GAME_INT fps, GAME_FLT dt); //this initializes or constructs all the properties of the class
    void Reset(); //destroys the View and all Objects stored in objects and and resets it to size zero;
    bool LoadLevel(std::string configFile); //constructs the View object and loads from XML file (by both parsing the XML and appropriate calls to the Art and Game Assets Libraries) and constructs all Objects in the objects container
    void Run(); //conducts a single frame of the game (Updating/Drawing/frame timing)
    void Update(); //calls the Update method of all Objects in objects
    void Draw(); //calls the Draw method of all Objects in objects

    GraphicsDevice* GetGraphicsDevice();
    InputDevice* GetInputDevice();
    b2World* GetWorld();
    GameAssetLibrary* GetGAssetLibrary();
    ArtAssetLibrary* GetAAssetLibrary();
    BodyAssetLibrary* GetBAssetLibrary();
    View* GetView();

private:
    //variables
    GameAssetLibrary* gLibrary;
    ArtAssetLibrary* aLibrary;
    BodyAssetLibrary* bLibrary;
    GraphicsDevice* gDevice;
    InputDevice* iDevice;
    View* view;
    Timer* timer;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> toDelete;
    GAME_INT fps;
    GAME_FLT gameTime; //maintains overall in-game time
    b2World* world;
    b2BodyDef bd;
    GAME_FLT dt;
};
