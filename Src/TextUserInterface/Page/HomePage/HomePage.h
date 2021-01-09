#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include "Route.h"
#include "Page.h"
#include "PageOption.h"

typedef struct type_HomePageData {
    int totalOptionCount;
    PageOptionID selectedOption;
} HomePageData;

PAGE_FUNCTION_TEMPLATE(Home)

Page* getNewHomePage();

#define HOME_PAGE_OPTION_NUM    6

#define HOME_PAGE_OPTION_ID_HOME    PAGE_ID_HOME
#define HOME_PAGE_OPTION_ID_PVP         1
#define HOME_PAGE_OPTION_ID_PVC         2
#define HOME_PAGE_OPTION_ID_PREANDSET   3
#define HOME_PAGE_OPTION_ID_ABOUTCHE    4
#define HOME_PAGE_OPTION_ID_ABOUTPRO    5
#define HOME_PAGE_OPTION_ID_EXIT        6

#define HOME_PAGE_OPTION_NAME_PVP           "<1> Player vs. Player"
#define HOME_PAGE_OPTION_NAME_PVC           "<2> Player vs. `Chessplayer`"
#define HOME_PAGE_OPTION_NAME_PREANDSET     "<3> Preferences & Settings"
#define HOME_PAGE_OPTION_NAME_ABOUTCHE      "<4> About `Chessplayer`"
#define HOME_PAGE_OPTION_NAME_ABOUTPRO      "<5> About `Gobang.Chessplayer.C`"
#define HOME_PAGE_OPTION_NAME_EXIT          "<6> Exit"

#endif // HOME_PAGE_H