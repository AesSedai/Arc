#include "Game.h"

#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "tinyxml2.h"

//Asset Library Wrappers
#include "GameAssetLibrary.h"
#include "ArtAssetLibrary.h"
#include "BodyAssetLibrary.h"

//Misc
#include "Texture.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Component.h"
#include "Timer.h"
#include "View.h"
#include "Common.h"
#include "Box2DDebugDraw.h"

Game::Game( void )
{
}

Game::~Game( void )
{
    if ( gLibrary ) { delete gLibrary; }
    if ( aLibrary ) { delete aLibrary; }
    if ( gDevice ) { delete gDevice; }
    if ( iDevice ) { delete iDevice; }
    if ( view ) { delete view; }
    if ( timer ) { delete timer; }
    if ( world ) { delete world; }
}

//this initializes or constructs all the properties of the class
bool Game::Initialize( GraphicsDevice* gDevice, InputDevice* iDevice, GAME_INT fps, GAME_FLT dt )
{
    this->gDevice = gDevice;
    this->iDevice = iDevice;
    this->fps = fps;
    this->dt = dt;

    timer = new Timer();

    //Construct Frame Timer
    if ( !timer->Initialize( this->fps ) ) {
        printf( "Frame Timer could not initialize in Game! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    gameTime = 0.0f;

    //create libraries
    gLibrary = new GameAssetLibrary();
    aLibrary = new ArtAssetLibrary();
    bLibrary = new BodyAssetLibrary();

    if ( !gLibrary->Initialize() )
    {
        printf( "Unable to initialize gLibrary in Game!\n" );
        return false;
    }

    if ( !aLibrary->Initialize( this->gDevice, "./Assets/Config/assets.xml" ) )
    {
        printf( "Unable to initialize aLibrary in Game!\n" );
        return false;
    }

    if ( !bLibrary->Initialize("./Assets/Config/assets.xml" ) )
    {
        printf( "Unable to initialize bLibrary in Game!\n" );
        return false;
    }

    //
    //Construct Physics World
    //
    const b2Vec2 gravity( RW2PW( ( GAME_FLT )0 ), RW2PW( ( GAME_FLT )0 ) );
    world = new b2World( gravity );

    //
    //Set-up debugging
    //
    Box2DDebugDraw* debugDraw = new Box2DDebugDraw();
    debugDraw->Initialize( gDevice );
    debugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_aabbBit ); //Turn on shape (red color) and aabb (green)

    //Add the Debug Draw to the world
    if ( debugDraw != nullptr )
    {
        world->SetDebugDraw( debugDraw );
    }

    return true;
}

//destroys the View and all Objects stored in objects and and resets it to size zero;
void Game::Reset()
{
    for ( auto obj : objects )
    {
        obj->~Object();
        obj.reset();
        std::cout << obj.use_count() << std::endl;
    }
    std::cout << "size: " << objects.size() << std::endl;

    while ( !objects.empty() )
    {
        std::cout << "size: " << objects.size() << std::endl;
        objects.pop_back();
        std::cout << "size: " << objects.size() << std::endl;
    }

    objects.clear();
    std::cout << "size: " << objects.size() << std::endl;

    if(view) delete view;
}

//constructs the View object and loads from XML file (by both parsing the XML and appropriate calls to the Art and Game Assets Libraries) and constructs all Objects in the objects container
bool Game::LoadLevel( std::string configFile )
{
    view = new View();
    gDevice->SetView( view );

    if ( !view->Initialize( iDevice, 0.0f, 0.0f ) )
    {
        printf( "View could not initialize in Game! SDL_ERROR: %s\n", SDL_GetError() );
        return false;
    }

    //Parse XML file
    tinyxml2::XMLDocument doc;
    if ( !doc.LoadFile( configFile.c_str() ) == tinyxml2::XML_NO_ERROR )
    {
        printf( "Error parsing XML document. Unable to retrieve document.\n" );
        return false;
    }

    //Get root
    tinyxml2::XMLNode* root;
    tinyxml2::XMLNode* node;

    root = doc.FirstChildElement( "Level" );
    if ( !root ) {
        printf( "Error parsing XML document. Unable to retrieve root.\n" );
        return false;
    }

    node = root->FirstChildElement();

    //Get child elements
    for ( node; node != nullptr; node = node->NextSiblingElement() )
    {
        std::string key = node->ToElement()->Attribute( "name" );
        std::cout << key << std::endl;
        ObjectFactory* toMake = gLibrary->Search( key );
        if ( toMake != nullptr )
        {
            std::shared_ptr<Object> obj = toMake->Create( this, node, key );
            if ( obj != nullptr ) { objects.push_back( obj ); }
            else std::cout << "Error making " << key << std::endl;
        }
    }

    std::cout << "Loaded " << objects.size() << " objects." << std::endl;

    return true;
}

//conducts a single frame of the game (Updating/Drawing/frame timing)
void Game::Run()
{
    timer->start();
    Update();
    view->Update( gameTime );
    world->Step( dt, 8, 3 );
    gDevice->Begin();
    gDevice->Draw();
    world->DrawDebugData();
    gDevice->Present();
    timer->fpsRegulate();
}

//calls the Update method of all Objects in objects
void Game::Update()
{
    for ( std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it != objects.end(); ++it )
    {
        ( *it )->Update();
    }
}

//calls the Draw method of all Objects in objects
void Game::Draw()
{
}

GraphicsDevice* Game::GetGraphicsDevice()
{
    return gDevice;
}

InputDevice* Game::GetInputDevice()
{
    return iDevice;
}

View* Game::GetView()
{
    return view;
}

b2World* Game::GetWorld()
{
    return world;
}

GameAssetLibrary* Game::GetGAssetLibrary()
{
    return gLibrary;
}

ArtAssetLibrary* Game::GetAAssetLibrary()
{
    return aLibrary;
}

BodyAssetLibrary* Game::GetBAssetLibrary()
{
    return bLibrary;
}
