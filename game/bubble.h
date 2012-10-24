#ifndef BUBBLE_H_INCLUDED
#define BUBBLE_H_INCLUDED

#include "sprite.h"
#include "constante.h"

#define BUBBLES_PER_PATTERN                    192
#define BUBBLES_START_X                        712
#define BUBBLES_START_Y                        300
#define BUBBLES_OFFSET                         4800
#define BUBBLES1_FILENAME           "media/gfx/bubble1.png"
#define BUBBLES2_FILENAME           "media/gfx/bubble2.png"
#define BUBBLES3_FILENAME           "media/gfx/bubble3.png"
#define BUBBLES4_FILENAME           "media/gfx/bubble4.png"
#define BUBBLE_PATTERN_FILE1         "media/scripts/bubbles1.txt"
#define BUBBLE_PATTERN_FILE2         "media/scripts/bubbles2.txt"
#define BUBBLE_PATTERN_FILE3         "media/scripts/bubbles3.txt"


class BubblePattern
{
public:
    Sprite bubble_pattern[BUBBLES_PER_PATTERN];
    bool init(const char* filename, bool use_transp);
    void update(); // type of notespeed : 1 = 4th, 2 = 8th, 3 = 12th, 4= 16th of notes...etc Used to sync on the rythm of the music.
                                    //Note: the game will not go further than 16th of notes, hence 4 should be the maximum used.
    SDL_Surface* pattern_surface;
    unsigned int note;
    float pattern_offset;
    int nb_samples; // i.e. nb of visible bubbles in the pattern
    bool fullcombo;

    void display();
    void cleanup();
    bool collision_with (const Sprite& sprite);
    bool load_pattern(const char* patternfile);
};


#endif // BUBBLE_H_INCLUDED
