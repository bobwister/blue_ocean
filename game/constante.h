#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

#define WIN_TITLE                   "Blue Ocean ~prototype~"
#define WIN_WIDTH                   800
#define WIN_HEIGHT                  600
#define GRAVITY                     5.0f
#define LIQUID_RESISTANCE_X         100.0f
#define WATER_RESISTANCE_Y          0.1f
#define AIR_RESISTANCE_Y            35.0f
#define MUSIC_OFFSET                181//216 // the music starts at 216, then you have to add SPACE_BETWEEN_BEATS for each beats of offset
#define MAX_SPRITE_TYPES            50 // total different types of sprites in the game , used by SurfaceManager
#define VERTICALLINE_FILENAME       "media/gfx/vertical_line.png"
#define LIFECOUNTER_FILENAME        "media/gfx/bob_lives_icon.png"
#define PAUSE_FILENAME              "media/gfx/hud_game_pause.png"
#define FULLCOMBO_FILENAME          "media/gfx/full_combo.png"
#define STARFISH1_FILENAME          "media/gfx/starfish1.png"
#define FONT_FILENAME               "media/fonts/vdj.ttf"
#define MAX_SCORE_DIGITS            10 // among which 6 digits are used for "Score:"

#endif // CONSTANTE_H_INCLUDED
