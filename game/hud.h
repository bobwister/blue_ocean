#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <SDL_ttf.h>
#include "sprite.h"
#include "constante.h"

#define MAX_POPUPS          5
#define MAX_POPUPS_TYPE     2
#define POPUP_START_X       150

class ScoreDisplay : public Sprite
{
public:

    TTF_Font *font;

    bool init();
    void update(int bobscore);
    void display();
};

class ScorePopup : public Sprite
{
public:
    //void update();
    int index_i;
    int index_j;
    ScorePopup();
};

enum PopupType
{
    FULL_COMBO,
    BIG_AIR,
};

class Popup
{
public:
    Sprite popup_array[MAX_POPUPS];
    SDL_Surface* popup_surface[MAX_POPUPS];
    int index;
    double start_time[MAX_POPUPS];
    PopupType type;

    bool init(const char* filename, int i, bool use_transp = false);
    void activate(int popup_type, float popup_y);
    void update();
    void display();
    void cleanup();

    Popup();
};

#endif // HUD_H_INCLUDED
