#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#include "constante.h"


#define SPEEDX                  200.0f        // pixels per second
#define BPM_MUSIC_1             200
#define SPACE_BETWEEN_BEATS     100.0f //

extern SDL_Surface* screen;

double getTime();

class Sprite
{
public:
    float x;
    float y;
    //float offsetX;
    SDL_Surface* surface;
    bool invisible;
    Sprite();
    int index_sample;
    bool init(const char* filename, float  x, float y, bool use_transp = false);
    //bool init(SDL_Surface* surface, float  x, float y, bool use_transp = false);
    void update();
    void display();
    void cleanup();
    bool collision_with (const Sprite& sprite);

};

struct Starfish : public Sprite
{
    void update();
};

class SurfaceManager
{

public:
    SurfaceManager();
    SDL_Surface* sprites_surface[MAX_SPRITE_TYPES];
    bool addsurface(const char* filemane, int index);
    void cleanup();
    enum SpriteType
    {
        SPRITE_BACKGROUND,//0
        SPRITE_BOB,//1
        SPRITE_VERTICALLINE,//2
        SPRITE_LIFECOUNTER,//3
        SPRITE_PAUSE,//4
        SPRITE_BUBBLES1,//5
        SPRITE_BUBBLES2,//6
        SPRITE_BUBBLES3,//7
        SPRITE_BUBBLES4,//8
        SPRITE_STARFISH1,//9
    };
    SpriteType index_SpriteType;



};


#endif // SPRITE_H_INCLUDED
