#include "PvcPrefabPage.h"
#include "SmartDisplay.h"
#include "TuiDefinitions.h"
#include "TuiUtility.h"
#include "TuiUserInteraction.h"
#include "AudioPlayer.h"
#include "ChessappDefinitions.h"
#include "GamePage/GamePage.h"
#include "ChessappDispatch.h"

Page* getNewPvcPrefabPage()
{
    Page* pvcPrefab = getNewDefaultPage();
    pvcPrefab->id = PAGE_ID_PVCPREFAB;
    pvcPrefab->name  = PAGE_NAME_PVCPREFAB;
    pvcPrefab->desc = PAGE_DESC_PVCPREFAB;
    pvcPrefab->displayFunc = displayPvcPrefabPage;
    pvcPrefab->updateFunc = updatePvcPrefabPage;
    pvcPrefab->releaseFunc = releasePvcPrefabPage;

    PvcPrefabPageData * rawData = noNullMalloc(sizeof(PvcPrefabPageData));
    rawData->totalOptionCount = PVCPREFAB_OPTION_NUM;
    rawData->selectedOption = PVCPREFAB_PAGE_OPTION_ID_PREVIOUS;
    rawData->selectedOrderOption = PVCPREFAB_PAGE_OPTION_ID_PLAYER_FIRST;
    rawData->selectedLevelOption = PVCPREFAB_PAGE_OPTION_ID_DRUNK_LEVEL;
    pvcPrefab->data = getNewPageData();
    pvcPrefab->data->masterPageId = pvcPrefab->id;
    pvcPrefab->data->rawData = rawData;

    return pvcPrefab;
}

#define printPvcPrefabOption(ABBR) \
    printOption(PVCPREFAB_PAGE_OPTION_NAME_ ## ABBR, PVCPREFAB_PAGE_OPTION_ID_ ## ABBR, selectedOption);

#define printPvcPrefabRadioOption(ABBR, ACTIVE_ID) \
    printRadioOption(PVCPREFAB_PAGE_OPTION_NAME_ ## ABBR, PVCPREFAB_PAGE_OPTION_ID_ ## ABBR, selectedOption, ACTIVE_ID);

void displayPvcPrefabPage(PageData* data)
{
    PvcPrefabPageData* pvcPrefabData = (PvcPrefabPageData*)(data->rawData);
    PageOptionID selectedOption = pvcPrefabData->selectedOption;
    PageOptionID selectedOrder = pvcPrefabData->selectedOrderOption;
    PageOptionID selectedLevel = pvcPrefabData->selectedLevelOption;

    clearAndPrintWithDoubleBuffer(
        printf(HOME_PAGE_DASHBOARD_FRAME);
        printf("\n\n");
        printPvcPrefabOption(PREVIOUS);
        printPvcPrefabRadioOption(PLAYER_FIRST, selectedOrder);
        printPvcPrefabRadioOption(MACHINE_FIRST, selectedOrder);
        printf("\n");
        printPvcPrefabRadioOption(DRUNK_LEVEL, selectedLevel);
        printPvcPrefabRadioOption(LOW_LEVEL, selectedLevel);
        printPvcPrefabRadioOption(MIDDLE_LEVEL, selectedLevel);
        printPvcPrefabRadioOption(HIGH_LEVEL, selectedLevel);
        printPvcPrefabRadioOption(RANDOM_LEVEL, selectedLevel);
        printf("\n");
        printPvcPrefabOption(START_GAME);
        printf(PROMPT);
    );
}

Route* updatePvcPrefabPage(PageData* data, Route* routePassByPvcPrefab)
{
    PvcPrefabPageData * pvcPrefabData = (PvcPrefabPageData*)(data->rawData);
    PageID currentPageId = data->masterPageId;
    int currentPageOptionCount = pvcPrefabData->totalOptionCount;

    PageOptionID option = getValidPageOptionFromUser(currentPageId, currentPageOptionCount);
    playButtonSound();

    if (option == PAGE_OPTION_ID_CONFIRM) {

        switch (pvcPrefabData->selectedOption)
        {
            case PVCPREFAB_PAGE_OPTION_ID_PREVIOUS:
            {
                routePassByPvcPrefab->status = ROUTE_OVER;
                routePassByPvcPrefab->exitStatus = ROUTE_EXIT_SUCCESS;
                break;
            }
            case PVCPREFAB_PAGE_OPTION_ID_PLAYER_FIRST:
            case PVCPREFAB_PAGE_OPTION_ID_MACHINE_FIRST:
            {
                pvcPrefabData->selectedOrderOption = pvcPrefabData->selectedOption;
                routePassByPvcPrefab->status = ROUTE_CONTINUE;
                break;
            }
            case PVCPREFAB_PAGE_OPTION_ID_DRUNK_LEVEL:
            case PVCPREFAB_PAGE_OPTION_ID_LOW_LEVEL:
            case PVCPREFAB_PAGE_OPTION_ID_MIDDLE_LEVEL:
            case PVCPREFAB_PAGE_OPTION_ID_HIGH_LEVEL:
            case PVCPREFAB_PAGE_OPTION_ID_RANDOM_LEVEL:
            {
                pvcPrefabData->selectedLevelOption = pvcPrefabData->selectedOption;
                routePassByPvcPrefab->status = ROUTE_CONTINUE;
                break;
            }
            case PVCPREFAB_PAGE_OPTION_ID_START_GAME:
            {
                GamePrefabConfig* gamePrefabConfig = getGamePrefabConfig(
                    GAME_MODE_PVC,
                    getGameOrderFromOrderOptionID(pvcPrefabData->selectedOrderOption),
                    getGameLevelFromLevelOptionID(pvcPrefabData->selectedLevelOption)
                );
                Page* pvcPage = getNewGamePage(gamePrefabConfig);
                routePassByPvcPrefab = startRoutine(getGlobalTuiPageStack(), pvcPage, routePassByPvcPrefab);
                break;
            }
            default:
            {
                abortWithMsg("Unknown option of preferences and settings page.");
            }
        }
        if (routePassByPvcPrefab->exitStatus == ROUTE_EXIT_FAILURE) {
            routePassByPvcPrefab->status = ROUTE_OVER;
        }
    }
    else {
        pvcPrefabData->selectedOption = option;
        routePassByPvcPrefab->status = ROUTE_CONTINUE;
    }
    return routePassByPvcPrefab;
}

void releasePvcPrefabPage(PageData** data)
{
    PvcPrefabPageData* pvcPrefabData = (PvcPrefabPageData*)((*data)->rawData);
    free(pvcPrefabData);
    free(*data);
    *data = NULL;
}