#ifndef CHESSAPP_GLOBAL_CONFIG_H
#define CHESSAPP_GLOBAL_CONFIG_H

#include "ChessappDefinitions.h"
#include "AudioPlayer.h"
#include "NetworkManager.h"

#define DEFAULT_CONFIG_FILE_PATH    "./chessapp.config"

#define printChessappUsage() do { \
    printf("Usage: chessapp [-c filename]\n"); \
} while (0)

#define readConfigFilePathFromCmdArgs(VARIABLE) do { \
    for (int i = 1; i < argc; ++i) { \
        if (argv[i][0] == '-') { \
            switch (argv[i][1]) \
            { \
                case 'c': \
                { \
                    if ((i + 1) < argc) { \
                        VARIABLE = argv[++i]; \
                        break; \
                    } \
                } \
                default: \
                { \
                    printChessappUsage();            \
                    printf("Invalid argument: %s\n", argv[i]); \
                    exit(EXIT_FAILURE); \
                } \
            } \
        } \
        else { \
            printChessappUsage(); \
            exit(EXIT_FAILURE); \
        } \
    } \
} while (0)

typedef struct type_GlobalConfig {
    AudioConfig* audio;
    NetworkConfig* network;
} GlobalConfig;

GlobalConfig* getNewDefaultGlobalConfig();

GlobalConfig* getNewGlobalConfigFromCurrentGlobalStatus();

void readGlobalConfigFromConfigFile(const char* configFilePath);

void writeGlobalConfigToConfigFile(const char* configFilePath);

void releaseGlobalConfig(GlobalConfig** config);

#endif // CHESSAPP_GLOBAL_CONFIG_H
