#ifndef GAME_PREFAB_CONFIG_H
#define GAME_PREFAB_CONFIG_H

#include "ChessappDefinitions.h"
#include "CoreDefinitions.h"

typedef int GameMode;
typedef int GameOrder;
typedef int GameLevel;

typedef struct type_GamePrefabConfig {
    GameMode mode;
    GameOrder order;
    GameLevel level;
    Side userSide;
    Side machineSide;
} GamePrefabConfig;

GamePrefabConfig* getGamePrefabConfig(GameMode mode, GameOrder order, GameLevel level);

#define getPageIdFromGameMode(MODE) ((MODE) == GAME_MODE_PVP ? PAGE_ID_PVP : PAGE_ID_PVC)
#define getPageNameFromGameMode(MODE) ((MODE) == GAME_MODE_PVP ? PAGE_NAME_PVP : PAGE_NAME_PVC)
#define getPageDescFromGameMode(MODE) ((MODE) == GAME_MODE_PVP ? PAGE_DESC_PVP : PAGE_DESC_PVC)

void releaseGamePrefabConfig(GamePrefabConfig** config);

/* Game mode */
#define GAME_MODE_PVP    0
#define GAME_MODE_PVC    1

#define isGameModePvP(MODE) ((MODE) == GAME_MODE_PVP)

/* Game order */
#define GAME_ORDER_PLAYER_FIRST          10
#define GAME_ORDER_CHESSPLAYER_FIRST     20

#define isGameOrderPlayerFirst(ORDER) ((ORDER) == GAME_ORDER_PLAYER_FIRST)

/* Game level */
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
/* Oops! Chessplayer is drunk. You win for sure. */
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
#define GAME_LEVEL_DRUNK  -100

#define GAME_LEVEL_LOW      0
#define GAME_LEVEL_MIDDLE   1
#define GAME_LEVEL_HIGH     2

#define GAME_LEVEL_RANDOM    25

#define getCorePrefabConfigSideFromGameSide(SIDE) (\
    (SIDE) == SIDE_BLACK ? CPC_SIDE_BLACK : \
    (SIDE) == SIDE_WHITE ? CPC_SIDE_WHITE : \
    CPC_SIDE_EMPTY \
    )

#define getCorePrefabConfigLevelFromGameLevel(LEVEL) ( \
    (LEVEL) == GAME_LEVEL_DRUNK ? CPC_LEVEL_DRUNK : \
    (LEVEL) == GAME_LEVEL_LOW ? CPC_LEVEL_LOW : \
    (LEVEL) == GAME_LEVEL_MIDDLE ? CPC_LEVEL_MIDDLE : \
    (LEVEL) == GAME_LEVEL_HIGH ? CPC_LEVEL_HIGH : \
    CPC_LEVEL_RANDOM \
)

#endif // GAME_PREFAB_CONFIG_H