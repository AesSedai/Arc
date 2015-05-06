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
        std::string name = node->ToElement()->Attribute("name");
        std::string shape = node->ToElement()->Attribute("shape");

        if(shape.compare("polygon") == 0)
        {
            b2PolygonShape* s = new b2PolygonShape;
            std::vector<b2Vec2> vertices;
            std::string c = node->ToElement()->Attribute("coords");
            std::vector<std::string> coords;
            boost::split(coords, c, boost::is_any_of(","), boost::token_compress_on);

            for(int i = 0; i < coords.size(); i = i + 2)
            {
                std::cout << coords[i] << ", " << coords[i+1] << std::endl;
                vertices.push_back(b2Vec2(RW2PW(boost::lexical_cast<GAME_INT>(coords[i])), RW2PW(boost::lexical_cast<GAME_INT>(coords[i+1]))));
            }

            s->Set(vertices.data(), vertices.size());

            library.insert(std::pair<std::string, b2Shape*>(name, s));
        }
        if(shape.compare("circle") == 0)
        {
            b2CircleShape* s = new b2CircleShape;
            GAME_INT radius = boost::lexical_cast<GAME_INT>(node->ToElement()->Attribute("radius"));
            s->m_radius = RW2PW(radius);
            library.insert(std::pair<std::string, b2Shape*>(name, s));
        }
    }

    std::cout << "Loaded " << library.size() << " Body assets." << std::endl;

    return true;
}

b2Shape* BodyAssetLibrary::Search(std::string string)
{
    std::map<std::string, b2Shape*>::iterator it = library.find(string);
    if(it != library.end())
    {
        return it->second;
    }
    return nullptr;
}
