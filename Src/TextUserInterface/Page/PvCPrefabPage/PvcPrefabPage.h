#ifndef PVC_PREFAB_PAGE_H
#define PVC_PREFAB_PAGE_H

#include "Route/Route.h"
#include "Page/Page.h"
#include "Page/PageOption.h"

typedef struct type_PvcPrefabPageData {
    int totalOptionCount;
    PageOptionID selectedOption;
    PageOptionID selectedOrderOption;
    PageOptionID selectedLevelOption;
} PvcPrefabPageData;

PAGE_FUNCTION_TEMPLATE(PvcPrefab)

Page* getNewPvcPrefabPage();

#define PVCPREFAB_OPTION_NUM    10

#define PVCPREFAB_PAGE_OPTION_ID_PVCPREFAB  PAGE_ID_PVCPREFAB
#define PVCPREFAB_PAGE_OPTION_ID_PREVIOUS           61
#define PVCPREFAB_PAGE_OPTION_ID_PLAYER_FIRST       62
#define PVCPREFAB_PAGE_OPTION_ID_MACHINE_FIRST      63
#define PVCPREFAB_PAGE_OPTION_ID_DRUNK_LEVEL        64
#define PVCPREFAB_PAGE_OPTION_ID_LOW_LEVEL          65
#define PVCPREFAB_PAGE_OPTION_ID_MIDDLE_LEVEL       66
#define PVCPREFAB_PAGE_OPTION_ID_HIGH_LEVEL         67
#define PVCPREFAB_PAGE_OPTION_ID_RANDOM_LEVEL       68
#define PVCPREFAB_PAGE_OPTION_ID_START_GAME         69

#define PVCPREFAB_PAGE_OPTION_NAME_PREVIOUS         "<1> Previous Page"
#define PVCPREFAB_PAGE_OPTION_NAME_PLAYER_FIRST     "<2> Player First"
#define PVCPREFAB_PAGE_OPTION_NAME_MACHINE_FIRST    "<3> Machine First"
#define PVCPREFAB_PAGE_OPTION_NAME_DRUNK_LEVEL      "<4> Play with Drunkard"
#define PVCPREFAB_PAGE_OPTION_NAME_LOW_LEVEL        "<5> Low Level"
#define PVCPREFAB_PAGE_OPTION_NAME_MIDDLE_LEVEL     "<6> Middle Level"
#define PVCPREFAB_PAGE_OPTION_NAME_HIGH_LEVEL       "<7> High Level"
#define PVCPREFAB_PAGE_OPTION_NAME_RANDOM_LEVEL     "<8> Choose a Level Randomly"
#define PVCPREFAB_PAGE_OPTION_NAME_START_GAME       "<9> Start Game"

#define getGameOrderFromOrderOptionID(ID) \
    ((ID) == PVCPREFAB_PAGE_OPTION_ID_PLAYER_FIRST ? GAME_ORDER_PLAYER_FIRST : \
    GAME_ORDER_CHESSPLAYER_FIRST)

#define getGameLevelFromLevelOptionID(ID) \
    ((ID) == PVCPREFAB_PAGE_OPTION_ID_DRUNK_LEVEL ? GAME_LEVEL_DRUNK : \
    (ID) == PVCPREFAB_PAGE_OPTION_ID_LOW_LEVEL ? GAME_LEVEL_LOW : \
    (ID) == PVCPREFAB_PAGE_OPTION_ID_MIDDLE_LEVEL ? GAME_LEVEL_MIDDLE : \
    (ID) == PVCPREFAB_PAGE_OPTION_ID_HIGH_LEVEL ? GAME_LEVEL_HIGH : \
    GAME_LEVEL_RANDOM)

#endif // PVC_PREFAB_PAGE_H