#include "AudioPlayer.h"
#include "ChessappDefinitions.h"

#include <stdlib.h>

void initializeGlobalAudioConfig(const AudioConfig* config)
{
    IS_GLOBAL_AUDIO_ENABLED = config->isGlobalAudioEnabled;
}

AudioConfig* getNewDefaultAudioConfig()
{
    AudioConfig* config = (AudioConfig*)noNullMalloc(sizeof(AudioConfig));
    config->isGlobalAudioEnabled = true;
    return config;
}

AudioConfig* getNewAudioConfigFromCurrentAudioStatus()
{
    AudioConfig* config = (AudioConfig*)noNullMalloc(sizeof(AudioConfig));
    config->isGlobalAudioEnabled = IS_GLOBAL_AUDIO_ENABLED;
    return config;
}

void releaseAudioConfig(AudioConfig** config)
{
    free(*config);
    *config = NULL;
}