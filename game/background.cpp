#include "background.h"
#include "audio.h"
#include "math.h"
#include "sprite.h"

//bool Background::init(SDL_Surface* surface, float  x, float y, bool use_transp)
bool Background::init(const char* filename, float  x, float y, bool use_transp)
{
    sprite1.init(filename, x, y);
    sprite2.init(filename, x + WIN_WIDTH*4, y);
    return true;
}

 void Background::update()
{
    sprite1.x = ( - (getTime() - music_start_time) * BPM_MUSIC_1 / 60 * 100);
    loop_counter = (int)(-sprite1.x / (WIN_WIDTH*4));
    sprite1.x += WIN_WIDTH*4 * (loop_counter);

    /*if (sprite1.x < -WIN_WIDTH*2)
    {
        sprite1.x += WIN_WIDTH*4;
    }*/

    sprite2.x = sprite1.x + WIN_WIDTH*4;

    sprite2.y = sprite1.y;
}

void Background::display()
{
    sprite1.display();
    sprite2.display();
}

void Background::cleanup()
{
    sprite1.cleanup();
    sprite2.cleanup();
}


