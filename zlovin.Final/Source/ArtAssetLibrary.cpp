#include "ArtAssetLibrary.h"
#include "GraphicsDevice.h"
#include "Texture.h"
#include "View.h"
#include "tinyxml2.h"

ArtAssetLibrary::ArtAssetLibrary(void)
{
}

ArtAssetLibrary::~ArtAssetLibrary(void)
{
}

bool ArtAssetLibrary::Initialize(GraphicsDevice* gDevice, std::string path)
{
    this->gDevice = gDevice;

    //Parse XML file
    tinyxml2::XMLDocument doc;
    std::cout << tinyxml2::XMLError(doc.LoadFile(path.c_str())) << std::endl;
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

    node = root->FirstChildElement("Art");
    node = node->FirstChildElement("ArtAsset");

    //Get child elements
    for(node; node != nullptr; node = node->NextSibling())
    {
        std::string name = node->ToElement()->Attribute("name");
        std::string file = node->ToElement()->Attribute("file");

        library.insert(std::pair<std::string, Texture*>(name, new Texture()));
        if(!library.find(name)->second->load(gDevice->GetRenderer(), file))
        {
            std::cout << "Error loading " << name << " in " << file << " Art Asset." << std::endl;
            return false;
        }
    }

    std::cout << "Loaded " << library.size() << " art assets." << std::endl;

    return true;
}

Texture* ArtAssetLibrary::Search(std::string string)
{
    std::map<std::string, Texture*>::iterator it = library.find(string);
    if(it != library.end())
    {
        return it->second;
    }
    return nullptr;
}
