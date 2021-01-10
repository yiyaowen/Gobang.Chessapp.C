#include "AboutChePage.h"
#include "ChessappDefinitions.h"
#include "TuiUtility.h"
#include "SmartDisplay.h"

Page* getNewAboutChePage()
{
    Page* aboutChe = getNewDefaultPage();
    aboutChe->id = PAGE_ID_ABOUTCHE;
    aboutChe->name = PAGE_NAME_ABOUTCHE;
    aboutChe->desc = PAGE_DESC_ABOUTCHE;
    aboutChe->displayFunc = displayAboutChePage;
    aboutChe->updateFunc = updateAboutChePage;
    aboutChe->releaseFunc = releaseAboutChePage;

    AboutChePageData* rawData = noNullMalloc(sizeof(AboutChePageData));
    rawData->reserved = NULL;
    aboutChe->data = getNewPageData();
    aboutChe->data->masterPageId = aboutChe->id;
    aboutChe->data->rawData = rawData;

    return aboutChe;
}

void printAboutChePageContent()
{
    printf(ABOUT_CHESSPLAYER_CONTENT);
}

void displayAboutChePage(PageData* data)
{
    clearAndPrintWithDoubleBuffer(
        printf(HOME_PAGE_DASHBOARD_FRAME);
        printf("\n\n");

        printAboutChePageContent();

        printf("\n");
        printf(PROMPT);
    );
}

Route* updateAboutChePage(PageData* data, Route* routePassByAboutChe)
{
    AboutChePageData* aboutCheData = (AboutChePageData*)data->rawData;

    char c;

get_user_input:
    if ((c = (char)getchar()) != '\n') {
        clearInputBuffer();
    }
    if (c == 'q' || c == 'Q') {
        routePassByAboutChe->status = ROUTE_OVER;
        routePassByAboutChe->exitStatus = ROUTE_EXIT_SUCCESS;
        return routePassByAboutChe;
    }
    else {
        printWithDoubleBuffer(
            printf("Enter 'q' or 'Q' to quit.\n");
            printf(PROMPT);
        );
        goto get_user_input;
    }
}

void releaseAboutChePage(PageData** data)
{
    AboutChePageData* aboutCheData = (AboutChePageData*)((*data)->rawData);
    free(aboutCheData);
    free(*data);
    *data = NULL;
}