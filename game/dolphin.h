#ifndef DOLPHIN_H_INCLUDED
#define DOLPHIN_H_INCLUDED

#include "sprite.h"
#include "background.h"
#include "constante.h"
#include "hud.h"


#define BOB_FILENAME                "media/gfx/bob2.png"
#define BOB_START_X                 75
#define BOB_START_Y                 300
#define BOB_ACCELERATION_X          1000.0f
#define BOB_ACCELERATION_Y          7.0f
#define BOB_MAX_ACCELERATION_Y      30.0f
#define BOB_MAX_SPEED_X             5.0f
#define BOB_MAX_SPEED_Y             7.0f
#define BOB_START_LIVES             5
#define BOB_MAX_LIVES               10
#define BOB_INVINCIBLE_DURATION     3
#define BOB_MIN_X                   100
#define BOB_MAX_X                   600
#define BOB_MIN_Y                   0 // 105
#define BOB_MAX_Y                   430
#define BOB_START_SCORE             0
#define BOB_SPEED_FOR_AIR_START     4.0f // speed necessary to jump out of water
#define BOB_Y_FOR_AIR_START         150 // y necessary to jump out of water, cancel acceleration
#define BOB_Y_FOR_BIG_AIR           100 // slows the speed of falling if Bob reaches this height

struct Dolphin : public Sprite
{
    float speed_x;
    float speed_y;
    float acceleration_y;
    int deceleration;
    int lives;
    bool invincible;
    double invincible_timer;
    bool invisible;
    double invisible_timer;
    float camera_x;
    float camera_y;
    int score;
    int combo_pattern;
    bool air; //out of water
    bool big_air; //big jump
    bool back_from_air; //when you just come back from an air jump

    Dolphin();
    void update(double elapsed, const SDL_Event& event);
    void setInvincible ();
};




#endif // DOLPHIN_H_INCLUDED
