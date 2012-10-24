#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "sprite.h"
#include "constante.h"

#define BACKGROUND_FILENAME "media/gfx/background.png"

struct Background
{
    Sprite sprite1; //to be renamed "water"
    Sprite sprite2;
    float starting_time;
    int loop_counter; //used for looping the background scrolling
    /*Sprite floor;
    Sprite incoming_floor;
    Sprite sky;
    Sprite incoming_sky;*/
    bool init(const char* filename, float  x, float y, bool use_transp = false);
    //bool init(SDL_Surface* surface_arg, float  x, float y, bool use_transp = false);
    void update();
    void display();
    void cleanup();
};

#endif // BACKGROUND_H_INCLUDED
