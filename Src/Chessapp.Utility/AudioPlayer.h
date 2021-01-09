#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <windows.h>

#pragma comment(lib, "winmm.lib")

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

#define playSoundResource(NAME) do { \
 if (IS_GLOBAL_AUDIO_ENABLED) \
        PlaySound(TEXT(NAME), NULL, SND_RESOURCE | SND_ASYNC); \
} while (0)

#define playButtonSound() do { \
    playSoundResource("ChangeOption"); \
} while (0)

#define playMoveSound() do { \
    playSoundResource("MovePiece"); \
} while (0)

#define playPlayerWinSound() do { \
    playSoundResource("PlayerWin"); \
} while (0)

#define playMachineWinSound() do { \
    playSoundResource("MachineWin"); \
} while (0)

#endif // AUDIO_PLAYER_H