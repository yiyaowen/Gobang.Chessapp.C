#include "GamePrefabConfig.h"

#include <stdlib.h>

GamePrefabConfig* getGamePrefabConfig(GameMode mode, GameOrder order, GameLevel level)
{
    GamePrefabConfig* config = (GamePrefabConfig*)malloc(sizeof(GamePrefabConfig));
    config->mode = mode;
    config->order = order;
    config->level = level;
    return config;
}

void releaseGamePrefabConfig(GamePrefabConfig** config)
{
    free(*config);
    *config = NULL;
}