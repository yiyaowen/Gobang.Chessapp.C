#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <stdbool.h>

#define IS_GLOBAL_NETWORK_ENABLED_CONFIG_KEY    "NetworkConfig.isGlobalNetworkEnabled"

typedef struct type_NetworkConfig {
    bool isGlobalNetworkEnabled;
} NetworkConfig;

void initializeGlobalNetworkConfig(const NetworkConfig* config);

NetworkConfig* getNewDefaultNetworkConfig();

NetworkConfig* getNewNetworkConfigFromCurrentNetworkStatus();

void releaseNetworkConfig(NetworkConfig** config);

bool IS_GLOBAL_NETWORK_ENABLED;

#define isGlobalNetworkEnabled() (IS_GLOBAL_NETWORK_ENABLED)

#define reverseGlobalNetworkStatus() do { \
    IS_GLOBAL_NETWORK_ENABLED = !IS_GLOBAL_NETWORK_ENABLED; \
} while (0)


#endif // NETWORK_MANAGER_H