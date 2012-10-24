#include "hud.h"
#include "audio.h"

#define SCOREDISPLAY_X          700
#define SCOREDISPLAY_Y          30
#define FONT_SIZE               20
#define COLOR_BLACK             (SDL_Color) {0,0,0}

#define POPUP_Y_OFSSET          150


/*ScoreDisplay::ScoreDisplay()
{

}*/

bool ScoreDisplay::init()
{
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return false;
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont(FONT_FILENAME, FONT_SIZE);
    return true;
}

void ScoreDisplay::update(int bobscore)//int bobscore)
{
    char score[MAX_SCORE_DIGITS];
    sprintf(score, "%d", bobscore);
    surface = TTF_RenderText_Blended(font, score, COLOR_BLACK); //"hello" => score
}

void ScoreDisplay::display()
{
    x = SCOREDISPLAY_X;
    y = SCOREDISPLAY_Y;
    if (!invisible)
        {
            SDL_Rect rect;
            rect.x = (int)x - surface-> w/2;
            rect.y = (int)y - surface-> h/2;
            SDL_BlitSurface(surface, NULL, screen, &rect);
        }
}

ScorePopup::ScorePopup()
{
    invisible = true;
}

Popup::Popup()
{
    index = 0;
    for (int i=0; i < MAX_POPUPS; i++)
        popup_array[i].invisible = true;
}

bool Popup::init(const char* filename, int i, bool use_transp)
{
    popup_surface[i] = IMG_Load(filename);

    // Setting the transparent color to orange
    SDL_SetColorKey(popup_surface[i], SDL_SRCCOLORKEY, SDL_MapRGB(popup_surface[i]->format, 255, 128, 0));

    if (use_transp)
        SDL_SetAlpha(popup_surface[i], SDL_SRCALPHA, 255);
    return true;
}

void Popup::activate(int popup_type, float popup_y)
{
    start_time[index] = getTime();
    popup_array[index].x = POPUP_START_X + SPACE_BETWEEN_BEATS/2*index;
    popup_array[index].y = popup_y - POPUP_Y_OFSSET;
    popup_array[index].invisible = false;
    popup_array[index].surface = popup_surface[popup_type];
    index++;
}

void Popup::update()
{
    index = 0;
    for (int i=0; i < MAX_POPUPS; i++)
    {
        if (popup_array[i].x < 0) //(popup_array[i].x - popup_array[i].surface->w/2 < 0)
            popup_array[i].invisible = true;
    }

    for (int i=0; i < MAX_POPUPS; i++)
    {
        if (!popup_array[i].invisible)
            index++;
        popup_array[i].x -= (getTime() - start_time[i]);
    }
}

void Popup::display()
{
    for (int i=0; i < MAX_POPUPS; i++)
        popup_array[i].display();
}

void Popup::cleanup()
{
    for (int i=0; i < MAX_POPUPS_TYPE; i++)
        SDL_FreeSurface(popup_surface[i]);
}
/*void ScorePopup::update()
{
    if (x < - surface->w/2) //while "full combo" is visible, update it so that it moves to the left
        invisible = true;
    double start_visible;
    double delta_t;
    if (invisible)
    {
        x = BPM_MUSIC_1;
        start_visible = getTime();
    }
    else
    {
        delta_t = getTime() - start_visible;
        float bps = BPM_MUSIC_1 / 60.0f; // beat per second
        x = - delta_t * SPACE_BETWEEN_BEATS * bps + MUSIC_OFFSET;
    }
    printf ("delta_t : %f\n", delta_t);
    printf ("popup x : %f\n", x);
}
*/
