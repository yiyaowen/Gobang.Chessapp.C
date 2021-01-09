#include "NetworkManager.h"

#include <stdlib.h>

void initializeGlobalNetworkConfig(const NetworkConfig* config)
{
    IS_GLOBAL_NETWORK_ENABLED = config->isGlobalNetworkEnabled;
}

NetworkConfig* getNewDefaultNetworkConfig()
{
    NetworkConfig* config = (NetworkConfig*)malloc(sizeof(NetworkConfig));
    config->isGlobalNetworkEnabled = false;
    return config;
}

NetworkConfig* getNewNetworkConfigFromCurrentNetworkStatus()
{
    NetworkConfig* config = (NetworkConfig*)malloc(sizeof(NetworkConfig));
    config->isGlobalNetworkEnabled = IS_GLOBAL_NETWORK_ENABLED;
    return config;
}

void releaseNetworkConfig(NetworkConfig** config)
{
    free(*config);
    *config = NULL;
}