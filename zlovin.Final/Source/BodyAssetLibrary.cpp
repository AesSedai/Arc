#include "BodyAssetLibrary.h"
#include "Common.h"
#include "tinyxml2.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <iostream>

BodyAssetLibrary::BodyAssetLibrary(void)
{
}

BodyAssetLibrary::~BodyAssetLibrary(void)
{
}

bool BodyAssetLibrary::Initialize(std::string path)
{
    //Parse XML file
    tinyxml2::XMLDocument doc;
    if(!doc.LoadFile(path.c_str()) == tinyxml2::XML_NO_ERROR)
    {
        printf("Error parsing XML document. Unable to retrieve Asset document.\n");
        return false;
    }

    //Get root
    tinyxml2::XMLNode* root;
    tinyxml2::XMLNode* node;

    root = doc.FirstChildElement("Assets");
    if(!root){
        printf("Error parsing XML document. Unable to retrieve Asset root.\n");
        return false;
    }

    node = root->FirstChildElement("Body");
    node = node->FirstChildElement("BodyAsset");

    //Get child elements
    for(node; node != nullptr; node = node->NextSibling())
    {
        fixture_params* params = new fixture_params;
        params->name = node->ToElement()->Attribute("name");
        params->shape = node->ToElement()->Attribute("shape");
        params->friction = std::stof(node->ToElement()->Attribute("friction"));
        params->density = std::stof(node->ToElement()->Attribute("density"));
        params->restitution = std::stof(node->ToElement()->Attribute("restitution"));

        if(params->shape.compare("circle") == 0)
        {
            params->radius = std::stof(node->ToElement()->Attribute("radius"));
            library.insert(std::pair<std::string, fixture_params*>(params->name, params));
        }
    }

    std::cout << "Loaded " << library.size() << " Body assets." << std::endl;

    return true;
}

b2FixtureDef* BodyAssetLibrary::Create(std::string string)
{
    std::map<std::string, fixture_params*>::iterator it = library.find(string);
    if(it != library.end())
    {
        if(it->second->shape.compare("circle") == 0)
        {
            b2FixtureDef* shapefd = new b2FixtureDef;
            b2CircleShape* shape = new b2CircleShape;
            shape->m_radius = RW2PW(it->second->radius);
            shapefd->shape = shape;
            shapefd->friction = it->second->friction;
            shapefd->density = it->second->density;
            shapefd->restitution = it->second->restitution;
            return shapefd;
        }
        else return nullptr;
    }
}