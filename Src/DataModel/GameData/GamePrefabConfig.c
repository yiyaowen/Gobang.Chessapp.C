#include "GamePrefabConfig.h"

#include <stdlib.h>

GamePrefabConfig* getGamePrefabConfig(GameMode mode, GameOrder order, GameLevel level)
{
    GamePrefabConfig* config = (GamePrefabConfig*)malloc(sizeof(GamePrefabConfig));
    config->mode = mode;
    config->order = order;
    config->level = level;
    if (isGameModePvP(mode)) {
        config->userSide = SIDE_BLACK;
        config->machineSide = SIDE_EMPTY;
    }
    else {
        if (isGameOrderPlayerFirst(order)) {
            config->userSide = SIDE_BLACK;
            config->machineSide = SIDE_WHITE;
        }
        else {
            config->userSide = SIDE_WHITE;
            config->machineSide = SIDE_BLACK;
        }
    }
    return config;
}

void releaseGamePrefabConfig(GamePrefabConfig** config)
{
    free(*config);
    *config = NULL;
}