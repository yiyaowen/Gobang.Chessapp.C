#include "ChessappGlobalConfig.h"
#include "StringPair.h"

#include <string.h>

GlobalConfig* getNewDefaultGlobalConfig()
{
    GlobalConfig* config = (GlobalConfig*)malloc(sizeof(GlobalConfig));
    config->audio = getNewDefaultAudioConfig();
    config->network = getNewDefaultNetworkConfig();
    return config;
}

GlobalConfig* getNewGlobalConfigFromCurrentGlobalStatus()
{
    GlobalConfig* config = (GlobalConfig*)malloc(sizeof(GlobalConfig));
    config->audio = getNewAudioConfigFromCurrentAudioStatus();
    config->network = getNewNetworkConfigFromCurrentNetworkStatus();
    return config;
}

void readGlobalConfigFromConfigFile(const char* configFilePath)
{
    GlobalConfig* config = getNewDefaultGlobalConfig();
    FILE* fileHandle = fopen(configFilePath, "r");
    if (fileHandle == NULL) {
        initializeGlobalAudioConfig(config->audio);
        initializeGlobalNetworkConfig(config->network);
        return;
    }

    char configLine[100];
    StringPairList* pairList = getNewStringPairListWithCapacity(10);
    while (fgets(configLine, 100, fileHandle)) {
        configLine[strlen(configLine) - 1] = '\0';
        StringPair* pair = splitStringToNewStringPairWithToken(configLine, "=");
        if (pair != NULL) {
            appendStringPairToStringPairList(pair, pairList);
        }
    }

    char* tmpValue;
    if ((tmpValue = getValueInStringPairListOfKey(pairList, IS_GLOBAL_AUDIO_ENABLED_CONFIG_KEY)) != NULL &&
        strcmp(tmpValue, "true") == 0)
    {
        config->audio->isGlobalAudioEnabled = true;
    }
    else {
        config->audio->isGlobalAudioEnabled = false;
    }
    if ((tmpValue = getValueInStringPairListOfKey(pairList, IS_GLOBAL_NETWORK_ENABLED_CONFIG_KEY)) != NULL &&
        strcmp(tmpValue, "true") == 0)
    {
        config->network->isGlobalNetworkEnabled = true;
    }
    else {
        config->network->isGlobalNetworkEnabled = false;
    }

    initializeGlobalAudioConfig(config->audio);
    initializeGlobalNetworkConfig(config->network);

    releaseStringPairList(&pairList);
    fclose(fileHandle);
    releaseGlobalConfig(&config);
}

void writeGlobalConfigToConfigFile(const char* configFilePath)
{
    GlobalConfig* config = getNewGlobalConfigFromCurrentGlobalStatus();
    FILE* fileHandle = fopen(configFilePath, "w");
    if (fileHandle == NULL) return;

    AudioConfig* audioConfig = config->audio;
    fprintf(fileHandle, "%s=%s\n", IS_GLOBAL_AUDIO_ENABLED_CONFIG_KEY,
        audioConfig->isGlobalAudioEnabled ? "true" : "false");
    NetworkConfig* networkConfig = config->network;
    fprintf(fileHandle, "%s=%s\n", IS_GLOBAL_NETWORK_ENABLED_CONFIG_KEY,
        networkConfig->isGlobalNetworkEnabled ? "true" : "false");

    fclose(fileHandle);
    releaseGlobalConfig(&config);
}

void releaseGlobalConfig(GlobalConfig** config)
{
    releaseAudioConfig(&((*config)->audio));
    releaseNetworkConfig(&((*config)->network));
    free(*config);
    *config = NULL;
}