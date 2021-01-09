#include "PreAndSetPage.h"
#include "TuiUtility.h"
#include "HomePage/HomePage.h"
#include "TuiUserInteraction.h"
#include "ChessappDefinitions.h"
#include "SmartDisplay.h"
#include "AudioPlayer.h"
#include "NetworkManager.h"

Page* getNewPreAndSetPage()
{
    Page* preAndSet = getNewDefaultPage();
    preAndSet->id = PAGE_ID_PREANDSET;
    preAndSet->name  = PAGE_NAME_PREANDSET;
    preAndSet->desc = PAGE_DESC_PREANDSET;
    preAndSet->displayFunc = displayPreAndSetPage;
    preAndSet->updateFunc = updatePreAndSetPage;
    preAndSet->releaseFunc = releasePreAndSetPage;

    PreAndSetPageData* rawData = malloc(sizeof(PreAndSetPageData));
    rawData->totalOptionCount = PREANDSET_OPTION_NUM;
    rawData->selectedOption = PREANDSET_PAGE_OPTION_ID_PREVIOUS;
    preAndSet->data = getNewPageData();
    preAndSet->data->masterPageId = preAndSet->id;
    preAndSet->data->rawData = rawData;

    return preAndSet;
}

#define printPreAndSetOption(ABBR) \
    printOption(PREANDSET_PAGE_OPTION_NAME_ ## ABBR, PREANDSET_PAGE_OPTION_ID_ ## ABBR, selectedOption);

#define printPreAndSetSwitchOption(ABBR, STATUS) \
    printSwitchOption(PREANDSET_PAGE_OPTION_NAME_ ## ABBR, PREANDSET_PAGE_OPTION_ID_ ## ABBR, selectedOption, STATUS);

void displayPreAndSetPage(PageData* data)
{
    PreAndSetPageData* preAndSetData = (PreAndSetPageData*)data->rawData;
    PageOptionID selectedOption = preAndSetData->selectedOption;

    clearAndPrintWithDoubleBuffer(
        printf(HOME_PAGE_DASHBOARD_FRAME);
        printf("\n\n");
        printPreAndSetOption(PREVIOUS);
        printPreAndSetSwitchOption(MUSICSOUND, isGlobalAudioEnabled());
        printPreAndSetSwitchOption(NETWORKCONFIG, isGlobalNetworkEnabled());
        printf(PROMPT);
    );
}

Route* updatePreAndSetPage(PageData* data, Route* routePassByPreAndSet)
{
    PreAndSetPageData* preAndSetData = (PreAndSetPageData*)data->rawData;
    PageID currentPageId = data->masterPageId;
    int currentPageOptionCount = preAndSetData->totalOptionCount;

    PageOptionID option = getValidPageOptionFromUser(currentPageId, currentPageOptionCount);
    playButtonSound();

    if (option == PAGE_OPTION_ID_CONFIRM) {

        switch (preAndSetData->selectedOption)
        {
            case PREANDSET_PAGE_OPTION_ID_PREVIOUS:
            {
                routePassByPreAndSet->status = ROUTE_OVER;
                routePassByPreAndSet->exitStatus = ROUTE_EXIT_SUCCESS;
                break;
            }
            case PREANDSET_PAGE_OPTION_ID_MUSICSOUND:
            {
                reverseGlobalAudioStatus();
                routePassByPreAndSet->status = ROUTE_CONTINUE;
                break;
            }
            case PREANDSET_PAGE_OPTION_ID_NETWORKCONFIG:
            {
                reverseGlobalNetworkStatus();
                routePassByPreAndSet->status = ROUTE_CONTINUE;
                break;
            }
            default:
            {
                abortWithMsg("Unknown option of preferences and settings page.");
            }
        }
        if (routePassByPreAndSet->exitStatus == ROUTE_EXIT_FAILURE) {
            routePassByPreAndSet->status = ROUTE_OVER;
        }
    }
    else {
        preAndSetData->selectedOption = option;
        routePassByPreAndSet->status = ROUTE_CONTINUE;
    }
    return routePassByPreAndSet;
}

void releasePreAndSetPage(PageData** data)
{
    PreAndSetPageData* preAndSetData = (PreAndSetPageData*)((*data)->rawData);
    free(preAndSetData);
    free(*data);
    *data = NULL;
}