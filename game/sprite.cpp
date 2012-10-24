#include "sprite.h"
#include "background.h"
#include "audio.h"
#include "assert.h"

#define STARFISH1_OFFSET        -1000


Sprite::Sprite()
{
    invisible = false;
}

SurfaceManager::SurfaceManager()
{
   for (int i=0; i < MAX_SPRITE_TYPES; i++)
    sprites_surface[i] = NULL;
}

bool SurfaceManager::addsurface(const char* filename, int index)
{
    sprites_surface[index] = IMG_Load(filename);
    if (!sprites_surface[index])
    {
        fprintf(stderr, "Error: could not load image \"%s\"", filename);
        return false;
    }
    return true;
}

void SurfaceManager::cleanup()
{
    for (int i=0; i < MAX_SPRITE_TYPES; i++)
        if(sprites_surface[i] != NULL)
            SDL_FreeSurface(sprites_surface[i]);
}

//bool Sprite::init(SDL_Surface* surface, float  x, float y, bool use_transp)
bool Sprite::init(const char* filename, float  x, float y, bool use_transp)
{
    //this->surface = surface;
    surface = IMG_Load(filename);
    this->x = x;
    this->y = y;

    // Setting the transparent color to orange
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 255, 128, 0));

    if (use_transp)
        SDL_SetAlpha(surface, SDL_SRCALPHA, 255);
    return true;
}

void Sprite::update()
{
    double delta_t = getTime() - music_start_time;
    float bps = BPM_MUSIC_1 / 60.0f; // beat per second
    x = - delta_t * SPACE_BETWEEN_BEATS * bps + MUSIC_OFFSET;
}

 void Starfish::update()
{
    double delta_t = getTime() - music_start_time;
    float bps = BPM_MUSIC_1 / 60.0f; // beat per second
    x = - delta_t * SPACE_BETWEEN_BEATS * bps + MUSIC_OFFSET + STARFISH1_OFFSET;
}

void Sprite::display()
{
    if (!invisible)
    {
        SDL_Rect rect;
        rect.x = (int)(x - surface-> w/2);
        rect.y = (int)(y - surface-> h/2);
        SDL_BlitSurface(surface, NULL, screen, &rect);
    }
}

void Sprite::cleanup()
{
    SDL_FreeSurface(surface);
}

bool Sprite::collision_with (const Sprite& sprite)
{
    if (sprite.invisible)
        return false;
    // Preliminary test : are they aligned ?
    else if (sprite.x - sprite.surface->w/2 > x + surface->w/2 //  |A| |B|

    || sprite.x + sprite.surface->w/2 < x - surface->w/2  //  |B| |A|


    || sprite.y + sprite.surface->h/2 < y - surface->h/2  //  |A|
                                                          //  |B|

    || sprite.y - sprite.surface->h/2 > y + surface->h/2) //  |B|
        return false;                                     //  |A|

    // Second test : are the corners included in the other sprite, or vice versa ?
    else
    {
        if ( (   ( (x - surface->w/2 < sprite.x - sprite.surface->w/2) && (sprite.x - sprite.surface->w/2 < x + surface->w/2)   // up-left corner
                && (y - surface->h/2 < sprite.y - sprite.surface->h/2) && (sprite.y - sprite.surface->h/2 < y + surface->h/2) )

            ||  ( (x - surface->w/2 < sprite.x + sprite.surface->w/2) && (sprite.x + sprite.surface->w/2 < x + surface->w/2)   // up-right corner
                && ( y - surface->h/2 < sprite.y - sprite.surface->h/2) && (sprite.y - sprite.surface->h/2 < y + surface->h/2) )

            ||  ( (x - surface->w/2 < sprite.x - sprite.surface->w/2) && (sprite.x - sprite.surface->w/2 < x + surface->w/2)   // down-left corner
                && (y - surface->h/2 < sprite.y + sprite.surface->h/2) && (sprite.y + sprite.surface->h/2 < y + surface->h/2) )

            ||  ( (x - surface->w/2 < sprite.x + sprite.surface->w/2) && (sprite.x + sprite.surface->w/2 < x + surface->w/2)   // down-right corner
                && (y - surface->h/2 < sprite.y + sprite.surface->h/2) && (sprite.y + sprite.surface->h/2 < y + surface->h/2))  )

         ||

              (  ((sprite.x - sprite.surface->w/2 < x - surface->w/2) && (x - surface->w/2 < sprite.x + sprite.surface->w/2)   // up-left corner
                && (sprite.y - sprite.surface->h/2 < y - surface->h/2) && (y - surface->h/2 < sprite.y + sprite.surface->h/2) )
                    //return true;
                || ( (sprite.x - sprite.surface->w/2 < x + surface->w/2) && (x + surface->w/2 < sprite.x + sprite.surface->w/2)  // up-right corner
                && (sprite.y - sprite.surface->h/2 < y - surface->h/2) && (y - surface->h/2 < sprite.y + sprite.surface->h/2) )
                    //return true;
                || ( (sprite.x - sprite.surface->w/2 < x - surface->w/2) && (x - surface->w/2 < sprite.x + sprite.surface->w/2)   // down-left corner
                && (sprite.y - sprite.surface->h/2 < y + surface->h/2) && (y + surface->h/2 < sprite.y + sprite.surface->h/2) )
                    //return true;
                || ( (sprite.x - sprite.surface->w/2 < x + surface->w/2) && (x + surface->w/2 < sprite.x + sprite.surface->w/2)   // down-right corner
                && (sprite.y - sprite.surface->h/2 < y + surface->h/2) && (y + surface->h/2 < sprite.y + sprite.surface->h/2))  )  )

            return true;
        else
            return false;
    }
    return false;
    assert(false && "forbidden");
}


