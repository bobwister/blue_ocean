#include "audio.h"



 /*SoundManager::SoundManager()
{

*/
double music_start_time = 0;

double getTime()
{
    Uint32 ms = SDL_GetTicks();
    return (double)ms / 1000.0;
}

void SoundManager::audioInit()
{

    FMOD_System_Create(&system);
    FMOD_System_Init(system, MAX_CHANNELS, FMOD_INIT_NORMAL, 0);

    FMOD_System_GetMasterChannelGroup(system, &master_channel);
    current_music = 0;
    current_sample = 0;

    for (int i=0; i<MAX_MUSICS; i++)
        music[i] = 0;

    for (int i=0; i<MAX_SAMPLES; i++)
        sample[i] = 0;

    for (int i=0; i<MAX_CHANNELS; i++)
        channel[i] = 0;

    result = FMOD_System_CreateSound(system, "media/sounds/ocean.ogg", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &music[current_music]);
    if (result != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire ocean.ogg\n");
        exit(EXIT_FAILURE);
    }

    FMOD_Sound_SetLoopCount(music[0], -1);

    for (int i=0; i<NB_MARIMBA_SAMPLES; i++)
    {
        char sample_filename[32];
        sprintf(sample_filename,"media/sounds/marimba%d.ogg", i);
        result = FMOD_System_CreateSound(system, sample_filename, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sample[current_sample]);
        if (result != FMOD_OK)
        {
            fprintf(stderr, "Impossible de lire marimba%d.ogg\n",i);
            exit(EXIT_FAILURE);
        }
        FMOD_Sound_SetLoopCount(sample[current_sample], 0);


        current_sample ++;
        current_sample = current_sample %NB_MARIMBA_SAMPLES;
    }


     /*result = FMOD_System_CreateSound(system, "bubble.wav", FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL, 0, &sample[0]);
    if (result != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire bubble.wav\n");
        exit(EXIT_FAILURE);
    }
    FMOD_Sound_SetLoopCount(sample[0], -1);*/
}

void SoundManager::cutoff_high_pass(bool high_pass_on)
{
    if (high_pass_on)
    {
        result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_LOWPASS, &high_pass);
        result = FMOD_DSP_SetParameter(high_pass, FMOD_DSP_LOWPASS_CUTOFF, 10000.0f);
        //result = system.getDSPHead();
         //another cool effect : #FMOD_DSP_ECHO_DELAY, 50;
        // FMOD_DSP_SetParameter(high_pass, FMOD_DSP_LOWPASS_CUTOFF, 1000);  <= lighter version of lowpass_cutoff
        result = FMOD_System_AddDSP(system, high_pass, dsp_connection);
    }

        // also exists for Channel or ChannelGroup types : FMOD_ChannelGroup_AddDSP(master_channel, high_pass, dsp_connection);

        // all FMOD_DSP_TYPE : http://www.2mal2mal.de/public/purebasic/includes/fmodex.pb

        //system.playDSP(FMOD_CHANNELINDEX channelid, DSP dsp, boolean paused, Channel channel)
        //Channel::getDSPHead
        //FMOD_RESULT F_API FMOD_System_CreateDSPByType        (FMOD_SYSTEM *system, FMOD_DSP_TYPE type, FMOD_DSP **dsp);
        //FMOD_RESULT F_API FMOD_System_CreateReverb           (FMOD_SYSTEM *system, FMOD_REVERB **reverb);
        //FMOD_RESULT F_API FMOD_System_SetReverbProperties    (FMOD_SYSTEM *system, const FMOD_REVERB_PROPERTIES *prop);
        //FMOD_RESULT F_API FMOD_System_GetDSPHead             (FMOD_SYSTEM *system, FMOD_DSP **dsp);


}

void SoundManager::echo(bool echo_on)
{
    if (echo_on)
    {
        result = FMOD_System_CreateDSPByType(system, FMOD_DSP_TYPE_LOWPASS, &ech);
        result = FMOD_DSP_SetParameter(ech, FMOD_DSP_ECHO_DELAY, 5000.0f);
        result = FMOD_System_AddDSP(system, ech, dsp_connection);
    }
}

void SoundManager::play()
{
    result = FMOD_System_PlaySound(system,FMOD_CHANNEL_FREE, music[current_music], 0, &channel[0]);
    music_start_time = getTime();

    //current_music++;
    //result = FMOD_System_PlaySound(system,FMOD_CHANNEL_FREE, sample[current_sample], 0, &channel[1]);
    //if (getTime()-music_start_time > 14)
    //result = FMOD_Channel_SetPosition(channel[0],0, FMOD_TIMEUNIT_MS);
}

void SoundManager::pause(bool pause)
{
    FMOD_ChannelGroup_SetPaused(master_channel, pause);
}

void SoundManager::playsample(int index)
{
    //current_sample = index;
    result = FMOD_System_PlaySound(system,FMOD_CHANNEL_FREE, sample[index], 0, &channel[1]);//current_sample], 0, &channel[1]);
    //current_sample++;
    //current_sample = current_sample %NB_MARIMBA_SAMPLES;
}

void SoundManager::cleanup()
{
    for (int i=0; i<MAX_MUSICS; i++)
        FMOD_Sound_Release(music[i]);
    for (int i=0; i<MAX_SAMPLES; i++)
        FMOD_Sound_Release(sample[i]);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}
