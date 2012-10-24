#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <fmodex/fmod.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define MAX_CHANNELS        8
#define MAX_MUSICS          5
#define MAX_SAMPLES         200
#define NB_MARIMBA_SAMPLES  44

extern double music_start_time;

double getTime();


struct SoundManager
{
    FMOD_SYSTEM *system;
    FMOD_RESULT result;
    FMOD_BOOL pause_sound;
    FMOD_SOUND *music[MAX_MUSICS]; // a music is a very long song designed to be played in loop
    int current_music;
    FMOD_SOUND *sample[MAX_SAMPLES]; // a sample is a very short sound, just a note, that will be triggered at a desired time
    int current_sample;
    FMOD_CHANNEL *channel [MAX_CHANNELS];
    FMOD_CHANNELGROUP *master_channel;
    FMOD_DSP *high_pass; // used for cut-off effect
    bool high_pass_on; //toggle the effect on/off
    FMOD_DSP *ech;
    bool echo_on;//toggle the effect on/off
    FMOD_DSPCONNECTION **dsp_connection;
    FMOD_DSPCONNECTION **dsp_connection2;

    //SoundManager();
    void audioInit();
    void cutoff_high_pass(bool high_pass_on = false);
    void echo(bool echo_on = false);

    void play();
    void playsample(int index_sample);
    void pause(bool pause = false);
    void cleanup();
};






#endif // AUDIO_H_INCLUDED
