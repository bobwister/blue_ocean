#include <stdio.h>
#include <stdlib.h>

#include "bubble.h"
#include "dolphin.h"
#include "math.h"
#include "audio.h"

bool BubblePattern::load_pattern(const char* patternfilename)
{
    FILE* f = fopen(patternfilename, "rb");
		if(!f)
		{
			fprintf(stderr, "Error: couldn't load \"%s\"", patternfilename);
			return false;
		}

		int i = -2;
		int j = 0;

		while(!feof(f))
		{
		    if (i < -1)
                fscanf(f, "%u\n", &note);
            else if (i < 0)
                fscanf(f, "%f\n", &pattern_offset);
            else
			{
                fscanf(f, "%f\n", &bubble_pattern[i].y);
                if (bubble_pattern[i].y < 0)
                    bubble_pattern[i].invisible = true;
                else
                {
                    bubble_pattern[i].y -= (bubble_pattern[i].y - (WIN_HEIGHT/2))*2;  //this line is optional and inverts the Y axis for more comfort in the patternfile
                    bubble_pattern[i].index_sample = j; // assigns the correct sound to the bubble
                    j++;
                }
            }
			i++;
		}
		nb_samples = j;

		fclose(f);
		for (int j=i; j<BUBBLES_PER_PATTERN; j++)
		{
            bubble_pattern[j].y = -1;
            bubble_pattern[j].invisible = true;
		}
		return true;
}

//bool BubblePattern::init(SDL_Surface* surface, float  x, float y, bool use_transp)
bool BubblePattern::init(const char* filename, bool use_transp)
{
    pattern_surface = IMG_Load(filename);
    for (int i=0; i<BUBBLES_PER_PATTERN; i++)
    {
        bubble_pattern[i].surface = pattern_surface;
    // Setting the transparent color to orange
        SDL_SetColorKey(bubble_pattern[i].surface, SDL_SRCCOLORKEY, SDL_MapRGB(bubble_pattern[i].surface->format, 255, 128, 0));
    if (use_transp)
        SDL_SetAlpha(bubble_pattern[i].surface, SDL_SRCALPHA, 255);
    }
    return true;
}

void BubblePattern::update()
{
    double delta_t = getTime() - music_start_time;
    float bps = BPM_MUSIC_1 / 60.0f; // beat per second
    for (int i=0; i<BUBBLES_PER_PATTERN; i++)
    {
        bubble_pattern[i].x = - delta_t * SPACE_BETWEEN_BEATS * bps + MUSIC_OFFSET + pattern_offset;//+ bubble_pattern[0].offsetX;
        bubble_pattern[i].x += i * SPACE_BETWEEN_BEATS / note; // divide by 4 for 16th notes
    }
}

void BubblePattern::display()
{
    for (int i=0; i<BUBBLES_PER_PATTERN; i++)
        bubble_pattern[i].display();
}

void BubblePattern::cleanup()
{
    SDL_FreeSurface (pattern_surface);
    pattern_surface = NULL;
}

bool BubblePattern::collision_with (const Sprite& sprite)
{
    for (int i=0; i<BUBBLES_PER_PATTERN; i++)
        if (bubble_pattern[i].collision_with(sprite))
            return true;
    return false;
}
