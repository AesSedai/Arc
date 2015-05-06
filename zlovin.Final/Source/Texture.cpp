#include <iostream>
#include "Texture.h"
#include "View.h"

Texture::Texture()
{
    width = 0;
    height = 0;
    texture = nullptr;
}

Texture::~Texture()
{
    free();
}

bool Texture::load( SDL_Renderer* renderer, std::string path )
{
    //Destroy existing texture information
    free();

    //The image that's loaded
    SDL_Surface* surface = nullptr;

    //Load the image
    surface = IMG_Load( path.c_str() );

    //If the image loaded
    if ( surface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 255, 0, 255 ) );

        //Create an optimized image
        texture = SDL_CreateTextureFromSurface( renderer, surface );

        if ( texture == nullptr )
        {
            printf( "Unable to create texture from image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Set the height and width from the texture
            SDL_QueryTexture( texture, nullptr, nullptr, &width, &height );

            //Free the loaded image; no longer needed
            SDL_FreeSurface( surface );
        }
    }

    return ( texture != nullptr );
}

void Texture::free()
{
    if ( texture != nullptr )
    {
        SDL_DestroyTexture( texture );
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture::renderEx( SDL_Renderer* renderer, int x, int y, float angle, View* v, SDL_Rect* clip )
{
    GAME_VEC vPos = v->getPosition();
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { int( x - vPos.x ), int( y - vPos.y ), width, height};

    //Set clip rendering dimensions
    if ( clip != nullptr ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, nullptr, SDL_FLIP_NONE );
}

int Texture::getWidth() {
    return ( width );
}

int Texture::getHeight() {
    return ( height );
}
