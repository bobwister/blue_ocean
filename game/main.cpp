// main.cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "audio.h"
#include "dolphin.h"
#include "bubble.h"
#include "constante.h"
#include <SDL_ttf.h>
#include "hud.h"

#define NB_BUBBLE_PATTERNS      3

SDL_Surface* screen;


// ========= Entry point ==========
int main(int argc, char *argv[])
{
    #ifdef WIN32
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );
    #endif
    printf("Welcome.\n");

    ScoreDisplay scoredisplay;

    Dolphin Bob;
    Background background;
    BubblePattern bubbles[NB_BUBBLE_PATTERNS];
    Sprite vertical_line;
    Sprite oxygen_bar;
    Sprite hud_game_pause;
    ScorePopup full_combo;
    Popup popup;
    Sprite life_counter[BOB_MAX_LIVES];
    Starfish starfish;
    SoundManager soundmanager;
    SurfaceManager surfacemanager;

    bool game_pause = false;

    // ############ Init() ##################

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption(WIN_TITLE, NULL);
    //SDL_WM_SetIcon(IMG_Load("bob_lives_icon.png"), NULL);

    screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        fprintf(stderr, "Impossible to load the video mode : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    scoredisplay.init();

    SDL_EnableKeyRepeat(10, -1);

    soundmanager.audioInit();
    soundmanager.play();

    // --- SurfaceManager ---
    /*
    if (!surfacemanager.addsurface(BACKGROUND_FILENAME, surfacemanager.SPRITE_BACKGROUND))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    if (!surfacemanager.addsurface(BOB_FILENAME, surfacemanager.SPRITE_BOB))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    if (!surfacemanager.addsurface(VERTICALLINE_FILENAME, surfacemanager.SPRITE_VERTICALLINE))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    if (!surfacemanager.addsurface(LIFECOUNTER_FILENAME, surfacemanager.SPRITE_LIFECOUNTER))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    if (!surfacemanager.addsurface(PAUSE_FILENAME, surfacemanager.SPRITE_PAUSE))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    if (!surfacemanager.addsurface(BUBBLES2_FILENAME, surfacemanager.SPRITE_BUBBLES2))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    if (!surfacemanager.addsurface(STARFISH1_FILENAME, surfacemanager.SPRITE_STARFISH1))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // --- Background ---
    if (!background.init(surfacemanager.surface_array[surfacemanager.SPRITE_BACKGROUND], WIN_WIDTH*2, WIN_HEIGHT/2, false))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // --- Bob ---
    if (!Bob.init(surfacemanager.surface_array[surfacemanager.SPRITE_BOB], BOB_START_X, BOB_START_Y, true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // --- Sprites ---

    if (!vertical_line.init(surfacemanager.surface_array[surfacemanager.SPRITE_VERTICALLINE], BOB_START_X+Bob.surface->w/2-1, BOB_START_Y, false)) // triggers the samples
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (!bubbles1.init(surfacemanager.surface_array[surfacemanager.SPRITE_BUBBLES2], (int)(BUBBLES_START_X), (int)(BUBBLES_START_Y), false))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    bubbles1.load_pattern(BUBBLE_PATTERN_FILE);

    if (!starfish.init(surfacemanager.surface_array[surfacemanager.SPRITE_STARFISH1], (int)(WIN_WIDTH*3/4), (int)(WIN_HEIGHT*2/3), false))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // --- HUD ---

    if (!hud_game_pause.init(surfacemanager.surface_array[surfacemanager.SPRITE_PAUSE], (int)(WIN_WIDTH/2), (int)(WIN_HEIGHT/2), true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }


    for (int i=0; i<BOB_MAX_LIVES; i++)
    {
        if (!life_counter[i].init(surfacemanager.surface_array[surfacemanager.SPRITE_LIFECOUNTER], (int)(WIN_WIDTH*(i+1)/20), (int)(WIN_HEIGHT*14/15), false))
        {
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    */

    // --- Background ---
    if (!background.init(BACKGROUND_FILENAME, WIN_WIDTH*2, WIN_HEIGHT/2, false))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // --- Bob ---
    if (!Bob.init(BOB_FILENAME, BOB_START_X, BOB_START_Y, true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // --- Sprites ---

    if (!vertical_line.init(VERTICALLINE_FILENAME, BOB_START_X+Bob.surface->w/2-1, BOB_START_Y, false)) // red vertical line that indicates the perfect timing for bubbles to be caught
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    for (int i=0; i < NB_BUBBLE_PATTERNS; i++)
    {
        char filename[32];
        sprintf(filename,"media/scripts/bubbles%d.txt", i);
        bubbles[i].load_pattern(filename);

        sprintf(filename,"media/gfx/bubble%d.png", bubbles[i].note);
        if (!bubbles[i].init(filename, false))
        {
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }

    if (!starfish.init(STARFISH1_FILENAME, -WIN_WIDTH*1/4, WIN_HEIGHT*2/3, false))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // --- HUD ---

    if (!hud_game_pause.init(PAUSE_FILENAME, WIN_WIDTH/2, WIN_HEIGHT/2, true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    popup.type=FULL_COMBO;
    /*if (!popup.popup_array[(int)(popup.type)].init("media/gfx/full_combo.png", -BOB_START_X, BOB_START_Y*1.5, true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }*/

    if (!popup.init("media/gfx/full_combo.png", (int)(popup.type), true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    popup.type=BIG_AIR;
    if (!popup.init("media/gfx/big_air.png", (int)(popup.type), true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /*if (!full_combo.init(FULLCOMBO_FILENAME, BOB_START_X + Bob.surface->w/2 + 50, BOB_START_Y - Bob.surface->h/2 - 50, true))
    {
        SDL_Quit();
        return EXIT_FAILURE;
    }*/


    for (int i=0; i<BOB_MAX_LIVES; i++)
    {
        if (!life_counter[i].init(LIFECOUNTER_FILENAME, WIN_WIDTH*(i+1)/20, WIN_HEIGHT*14/15, false))
        {
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }

    // ######## Main loop ########

    double now = getTime();
    double last_time = getTime();
    bool running = true;
    SDL_Event event;
    while (running)
    {
        last_time = now;
        now = getTime();

        double elapsed = now-last_time;

        while (SDL_PollEvent(&event))
        {
            switch (event.type) // Test du type d'évènement
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_p:
                        game_pause = !game_pause;
                        soundmanager.pause(game_pause);
                        break;
                    case SDLK_c:
                        soundmanager.high_pass_on = !soundmanager.high_pass_on;
                        soundmanager.cutoff_high_pass(soundmanager.high_pass_on);
                        break;
                    case SDLK_e:
                        soundmanager.echo_on = !soundmanager.echo_on;
                        soundmanager.echo(soundmanager.echo_on);
                        break;
                    default:
                        break;
                }
            case SDL_KEYUP:
                break;
            default:
                break;
            }
        }

        // ###### Update() #######

        if (!game_pause)
        {

            if (Bob.y < BOB_Y_FOR_BIG_AIR && !Bob.big_air)
            {
                popup.type = BIG_AIR;
                popup.activate ((int)(popup.type), Bob.y+200);
            }

            Bob.update(elapsed, event);
            background.sprite1.y -= Bob.camera_y;
            background.update();
            for (int i=0; i < NB_BUBBLE_PATTERNS; i++)
                bubbles[i].update();
            starfish.update();
            starfish.y -= Bob.camera_y;
            for (int i=0; i < popup.index ; i++)
                popup.popup_array[i].y -= Bob.camera_y;
            //full_combo.y -= Bob.camera_y;

            for (int i=0; i < NB_BUBBLE_PATTERNS; i++)
                for (int j=0; j<BUBBLES_PER_PATTERN; j++)
                    bubbles[i].bubble_pattern[j].y -= Bob.camera_y;



            // --- Collisions ---

            if (Bob.collision_with(starfish))
                if (!Bob.invincible)
                {
                    if (Bob.lives>0)
                        Bob.lives--;

                    Bob.setInvincible();
                }

            // Collision with any of the bubbles of any bubble pattern
            for (int i=0; i < NB_BUBBLE_PATTERNS; i++)
                for (int j=0; j<BUBBLES_PER_PATTERN; j++)
                    if (Bob.collision_with(bubbles[i].bubble_pattern[j]))
                    {
                        if (Bob.lives<BOB_MAX_LIVES)
                            Bob.lives++;


                            // --- Calculation of the combo for a given pattern ---
                            bubbles[i].fullcombo = false;
                            if (bubbles[i].bubble_pattern[j].index_sample == 0)
                            Bob.combo_pattern = 0;
                            if (Bob.combo_pattern < bubbles[i].bubble_pattern[j].index_sample+1)
                            {
                                Bob.combo_pattern++;
                                // When the player gets all the bubbles of a pattern, that's a "full combo"
                                if (Bob.combo_pattern == bubbles[i].nb_samples)
                                        bubbles[i].fullcombo = true;
                            }
                            else
                                Bob.combo_pattern = 0;
                            // --- Update of the score ---
                            Bob.score += bubbles[i].note;
                                // When a full combo occurs, all the points of the pattern are doubled
                            if (bubbles[i].fullcombo)
                            {
                                Bob.score += (Bob.combo_pattern * bubbles[i].note);
                                //full_combo.invisible = false;
                                //full_combo.index_i = i;
                                //full_combo.index_j = j;
                                popup.type = FULL_COMBO;
                                popup.activate((int)(popup.type), Bob.y);
                            }

                            bubbles[i].bubble_pattern[j].invisible = true;
                            // Calculation of the correct sample to play : find the right bubble pattern then add the index sample.
                            for (int k=0; k < i; k++)
                                bubbles[i].bubble_pattern[j].index_sample += bubbles[k].nb_samples;
                            soundmanager.playsample(bubbles[i].bubble_pattern[j].index_sample);
                    }

            scoredisplay.update(Bob.score);
            //printf ("y : %f\n", Bob.y);

            popup.update();
            // Update of the Full Combo sprite : it follows the last bubble of the pattern that was full combo-ed.
            // This bubble can be identified thanks to full_combo_index_i and full_combo_j, which values were stored on the collision.
            //full_combo.x = bubbles[full_combo.index_i].bubble_pattern[full_combo.index_j].x + Bob.surface->w/2;
            //full_combo.y = bubbles[full_combo.index_i].bubble_pattern[full_combo.index_j].y - Bob.surface->h/2;
        }

        // ###### Display() #######

        background.display();
        if (!Bob.invisible)
            Bob.display();
        for (int i=0; i < NB_BUBBLE_PATTERNS; i++)
            bubbles[i].display();
        //vertical_line.display();
        starfish.display();
        if (game_pause)
            hud_game_pause.display();

        /*for (int i=0 ; i < Bob.lives ; i++)
        {
            life_counter[i].display();
        }*/
        scoredisplay.display();
        popup.display();
        //full_combo.display();

        SDL_Flip(screen);
    }
    // ####### CleanUp() #########
    if (Bob.score == 176)
            printf("Congratz, you just scored 176 out of 176... BEAST1!!11!\n");
    Bob.cleanup();
    background.cleanup();
    for (int i=0; i < NB_BUBBLE_PATTERNS; i++)
    {
        bubbles[i].cleanup();
    }

    vertical_line.cleanup();
    starfish.cleanup();
    hud_game_pause.cleanup();
    //full_combo.cleanup();
    popup.cleanup();
    for (int i=0 ; i < BOB_MAX_LIVES ; i++)
        life_counter[i].cleanup();


    scoredisplay.cleanup();
    soundmanager.cleanup();
    //surfacemanager.cleanup();

    TTF_CloseFont(scoredisplay.font);
    TTF_Quit();

    SDL_Quit();

    return EXIT_SUCCESS;
}
