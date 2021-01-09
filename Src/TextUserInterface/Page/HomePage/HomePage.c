#include "HomePage.h"
#include "PageID.h"
#include "TuiUtility.h"
#include "TuiUserInteraction.h"
#include "ChessappDispatch.h"
#include "ChessappDefinitions.h"
#include "SmartDisplay.h"
#include "GamePrefabConfig.h"
#include "AudioPlayer.h"

#include "GamePage/GamePage.h"
#include "PreferencesAndSettingsPage/PreAndSetPage.h"
#include "AboutChessplayerPage/AboutChePage.h"
#include "AboutProjectPage/AboutProPage.h"
#include "PvCPrefabPage/PvcPrefabPage.h"


Page* getNewHomePage()
{
    Page* home = getNewDefaultPage();
    home->id = PAGE_ID_HOME;
    home->name = PAGE_NAME_HOME;
    home->desc = PAGE_DESC_HOME;
    home->displayFunc = displayHomePage;
    home->updateFunc = updateHomePage;
    home->releaseFunc = releaseHomePage;

    HomePageData* rawData = malloc(sizeof(HomePageData));
    rawData->totalOptionCount = HOME_PAGE_OPTION_NUM;
    rawData->selectedOption = HOME_PAGE_OPTION_ID_PVP;
    home->data = getNewPageData();
    home->data->masterPageId = home->id;
    home->data->rawData = rawData;

    return home;
}

#define printHomeOption(ABBR) \
    printOption(HOME_PAGE_OPTION_NAME_ ## ABBR, HOME_PAGE_OPTION_ID_ ## ABBR, selectedOption);

void displayHomePage(PageData* data)
{
    HomePageData* homeData = (HomePageData*)data->rawData;
    int selectedOption = homeData->selectedOption;

    clearAndPrintWithDoubleBuffer(
        printf(HOME_PAGE_DASHBOARD_FRAME);
        printf("\n\n");
        printHomeOption(PVP);
        printHomeOption(PVC);
        printHomeOption(PREANDSET);
        printHomeOption(ABOUTCHE);
        printHomeOption(ABOUTPRO);
        printHomeOption(EXIT);
        printf(PROMPT);
    );
}

Route* updateHomePage(PageData* data, Route* routePassByHome)
{
    HomePageData* homeData = (HomePageData*)data->rawData;
    PageID currentPageId = data->masterPageId;
    int currentPageTotalOptionCount = homeData->totalOptionCount;

    PageOptionID option = getValidPageOptionFromUser(currentPageId, currentPageTotalOptionCount);
    playButtonSound();

    if (option == PAGE_OPTION_ID_CONFIRM) {

        switch (homeData->selectedOption)
        {
            case HOME_PAGE_OPTION_ID_PVP:
            {
                GamePrefabConfig* gamePrefabConfig =
                    getGamePrefabConfig(GAME_MODE_PVP, GAME_ORDER_CHESSPLAYER_FIRST, GAME_LEVEL_DRUNK);
                Page* pvpPage = getNewGamePage(gamePrefabConfig);
                routePassByHome = startRoutine(getGlobalTuiPageStack(), pvpPage, routePassByHome);
                break;
            }
            case HOME_PAGE_OPTION_ID_PVC:
            {
                Page* pvcPrefabPage = getNewPvcPrefabPage();
                routePassByHome = startRoutine(getGlobalTuiPageStack(), pvcPrefabPage, routePassByHome);
                break;
            }
            case HOME_PAGE_OPTION_ID_PREANDSET:
            {
                Page* preAndSetPage = getNewPreAndSetPage();
                routePassByHome = startRoutine(getGlobalTuiPageStack(), preAndSetPage, routePassByHome);
                break;
            }
            case HOME_PAGE_OPTION_ID_ABOUTCHE:
            {
                Page* aboutChePage = getNewAboutChePage();
                routePassByHome = startRoutine(getGlobalTuiPageStack(), aboutChePage, routePassByHome);
                break;
            }
            case HOME_PAGE_OPTION_ID_ABOUTPRO:
            {
                Page* aboutProPage = getNewAboutProPage();
                routePassByHome = startRoutine(getGlobalTuiPageStack(), aboutProPage, routePassByHome);
                break;
            }
            case HOME_PAGE_OPTION_ID_EXIT:
            {
                routePassByHome->status = ROUTE_OVER;
                routePassByHome->exitStatus = ROUTE_EXIT_FAILURE;
                break;
            }
            default:
            {
                abortWithMsg("Unknown option of home page.");
            }
        }
        if (routePassByHome->exitStatus == ROUTE_EXIT_FAILURE) {
            routePassByHome->status = ROUTE_OVER;
        }
    }
    else {
        homeData->selectedOption = option;
        routePassByHome->status = ROUTE_CONTINUE;
    }
    return routePassByHome;
}

void releaseHomePage(PageData** data)
{
    HomePageData* homeData = (HomePageData*)((*data)->rawData);
    free(homeData);
    free(*data);
    *data = NULL;
}