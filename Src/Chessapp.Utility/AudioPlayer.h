#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <stdbool.h>
#include <stdio.h>

#define IS_GLOBAL_AUDIO_ENABLED_CONFIG_KEY  "AudioConfig.isGlobalAudioEnabled"

typedef struct type_AudioConfig {
    bool isGlobalAudioEnabled;
} AudioConfig;

void initializeGlobalAudioConfig(const AudioConfig* config);

AudioConfig* getNewDefaultAudioConfig();

AudioConfig* getNewAudioConfigFromCurrentAudioStatus();

void releaseAudioConfig(AudioConfig** config);

bool IS_GLOBAL_AUDIO_ENABLED;

#define isGlobalAudioEnabled() (IS_GLOBAL_AUDIO_ENABLED)

#define reverseGlobalAudioStatus() do { \
    IS_GLOBAL_AUDIO_ENABLED = !IS_GLOBAL_AUDIO_ENABLED; \
} while (0)

#define playBeepSound() do { \
    if (IS_GLOBAL_AUDIO_ENABLED) \
        printf("\a"); \
} while (0)

#endif // AUDIO_PLAYER_H