#pragma once

//C++ Libraries
#include <string>

//Dependencies
#include "SDL.h"
#include "SDL_image.h"

//Forward Declarations
class View;

class Texture{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool load(SDL_Renderer* renderer, std::string path );

    //Deallocates texture
    void free();

    //Renders texture at given point
    void renderEx(SDL_Renderer* renderer, int x, int y, float angle, View* v, SDL_Rect* clip = nullptr);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:

    //The actual hardware texture
    SDL_Texture* texture;
    View* view;

    //Image dimensions
    int width;
    int height;
};
