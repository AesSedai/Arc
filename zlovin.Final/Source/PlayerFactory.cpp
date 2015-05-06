#include "PlayerFactory.h"
#include "Game.h"
#include "Object.h"
#include "PlayerBehaviorComponent.h"
#include "BodyComponent.h"
#include "RenderComponent.h"
#include "ArtAssetLibrary.h"
#include "BodyAssetLibrary.h"

PlayerFactory::PlayerFactory(void)
{
}

PlayerFactory::~PlayerFactory(void)
{
}

std::shared_ptr<Object> PlayerFactory::Create(Game* g, tinyxml2::XMLNode* node, std::string name)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();

    //Find components
    node = node->FirstChildElement();
    for ( node; node != nullptr; node = node->NextSibling() )
    {
        tinyxml2::XMLElement* elem = node->ToElement();
        std::string c = elem->Name();
        if(c.compare("RenderComponent") == 0)
        {
            std::string n = elem->Attribute("name");
            std::shared_ptr<RenderComponent> sprite = std::make_shared<RenderComponent>(obj);
            sprite->Initialize(g->GetGraphicsDevice(), g->GetAAssetLibrary()->Search(n));
            obj->AddComponent(sprite);
        }
        if(c.compare("BodyComponent") == 0)
        {
            std::shared_ptr<BodyComponent> body = std::make_shared<BodyComponent>(obj);
            std::string n = elem->Attribute("name");
            float x = std::stof(elem->Attribute("x"));
            float y = std::stof(elem->Attribute("y"));
            float a = std::stof(elem->Attribute("angle"));
            body->Initialize(g->GetWorld(), g->GetBAssetLibrary()->Search(n), x, y, a);
            obj->AddComponent(body);
        }
    }

    //Create Components

    //Initialize Components
    //Render Component

    //Body Component

    //Behavior Component
    std::shared_ptr<PlayerBehaviorComponent> behavior = std::make_shared<PlayerBehaviorComponent>(obj);
    behavior->Initialize();
    behavior->SetInputDevice(g->GetInputDevice());
    behavior->SetView(g->GetView());

    obj->AddComponent(behavior);

    if(!obj->Initialize()) return nullptr;

    return obj;
}
