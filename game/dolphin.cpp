#include "dolphin.h"

Dolphin::Dolphin()
{
    speed_x = 0.0;
    speed_y = 0.0;
    acceleration_y = 0.0;
    deceleration = 1;
    lives = BOB_START_LIVES;
    invincible = false;
    invincible_timer = 0;
    invisible = false;
    camera_x = 0;
    camera_y = 0;
    score = BOB_START_SCORE;
    combo_pattern = 0;
    air = false;
    big_air = false;
    back_from_air = false;
}

void Dolphin::update(double elapsed, const SDL_Event& event)
{


    //float acceleration_x = -LIQUID_RESISTANCE_X;
    camera_x = x;
    camera_y = y;

    // if not keyboard input, this value will grow and grow to make the dolphin stop sliding
    deceleration ++;


    if (big_air)
        printf ("big_air\n");

    // Jump out of water -air start-
    if (y < BOB_Y_FOR_AIR_START)
    {
        air = true;
        back_from_air = true;
    }
    else
        air = false;

    if (y > BOB_Y_FOR_AIR_START + 10)
        back_from_air = false;


    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_SPACE:
                case SDLK_z:
                case SDLK_UP:
                    if (!air &&!back_from_air)
                    {
                            acceleration_y -= BOB_ACCELERATION_Y;
                            deceleration = 1;
                    }
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    if (!air)
                    {
                        acceleration_y += BOB_ACCELERATION_Y;
                        deceleration = 1;
                    }

                    break;
                case SDLK_RIGHT:
                    break;
                case SDLK_LEFT:
                    break;
                default:
                    break;
            }
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    break;
                case SDLK_DOWN:
                    break;
                default:
                    break;
            }
        default:
            break;
        }
    }

    // Apply acceleration constraints
    if (acceleration_y > BOB_MAX_ACCELERATION_Y)
        acceleration_y = BOB_MAX_ACCELERATION_Y;
    if (acceleration_y < -BOB_MAX_ACCELERATION_Y)
        acceleration_y = -BOB_MAX_ACCELERATION_Y;


    // Apply physics -gravity, liquid resistance etc...
    if (!air)
    {
        acceleration_y -= acceleration_y * WATER_RESISTANCE_Y;
        speed_y += acceleration_y * elapsed;
        // If no keyboard input from the player, the speed will decrease downto 0 as deceleration is incrementing
        speed_y = speed_y / deceleration;

    }
    else
    {
        acceleration_y += acceleration_y * AIR_RESISTANCE_Y;
        // Activate / Desactivate  Big Air
        if (y < BOB_Y_FOR_BIG_AIR)
            big_air = true;
        else
            big_air = false;
        //And now the falling down back to water
        if (big_air)
            speed_y += AIR_RESISTANCE_Y/2.5 * elapsed;
        else
            speed_y += AIR_RESISTANCE_Y/1.2 * elapsed;
    }



    //printf ("acceleration : %f\n", acceleration_y);
    //printf ("speed_y: %f\n",speed_y);
    printf ("y : %f\n", y);

    // Speed limitations
    if (speed_x > BOB_MAX_SPEED_X)
        speed_x = BOB_MAX_SPEED_X;
    if (speed_x < -BOB_MAX_SPEED_X)
        speed_x = -BOB_MAX_SPEED_X;
    if (speed_y > BOB_MAX_SPEED_Y)
        speed_y = BOB_MAX_SPEED_Y;
    if (speed_y < -BOB_MAX_SPEED_Y)
        speed_y = -BOB_MAX_SPEED_Y;

    // Apply the speed
    x += speed_x;
    y += speed_y;

    // Screen borders constraints to position
    if (x > WIN_WIDTH - surface->w/2)
    {
        speed_x = 0;
        x = WIN_WIDTH - surface->w/2;
    }
    if (x < surface->w/2)
    {
        speed_x = 0;
        x = surface->w/2;
    }

    if (y > BOB_MAX_Y)
    {
        speed_y = 0;
        y = BOB_MAX_Y;
    }

    if (y < BOB_MIN_Y)
    {
        speed_y = 0;
        y = BOB_MIN_Y;
    }

    camera_x = x - camera_x;
    camera_y = y - camera_y;
    //printf ("camera_y : %d\n", camera_y);
    //debug line
    //printf ("y : %d\n", (int)(y));

    // Invincibility timer : disactivates invincibility after BOB_INVINCIBLE_DURATION
    if (invincible)
        if (getTime() - invincible_timer > BOB_INVINCIBLE_DURATION)
            invincible = false;

    // Invisibility update
    if (invincible)
        invisible = (bool)((int)(getTime()*10.0) % 2);
    else
        invisible = false;



    // Apply air
    /*if (air)
    {
        // Air exit -dive-

        if (y < BOB_Y_FOR_AIR_START)
            air = false;

    }*/

}

void Dolphin::setInvincible () // used after collision with ennemy
{
        invincible = true;
        invincible_timer = getTime();
}


