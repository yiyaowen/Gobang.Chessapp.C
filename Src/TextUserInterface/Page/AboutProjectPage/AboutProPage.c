#include "AboutProPage.h"
#include "ChessappDefinitions.h"
#include "TuiUtility.h"
#include "SmartDisplay.h"

Page* getNewAboutProPage()
{
    Page* aboutPro = getNewDefaultPage();
    aboutPro->id = PAGE_ID_ABOUTPRO;
    aboutPro->name = PAGE_NAME_ABOUTPRO;
    aboutPro->desc = PAGE_DESC_ABOUTPRO;
    aboutPro->displayFunc = displayAboutProPage;
    aboutPro->updateFunc = updateAboutProPage;
    aboutPro->releaseFunc = releaseAboutProPage;

    AboutProPageData* rawData = malloc(sizeof(AboutProPageData));
    rawData->selectedOption = ABOUTPRO_PAGE_OPTION_ID_NORMAL;
    aboutPro->data = getNewPageData();
    aboutPro->data->masterPageId = aboutPro->id;
    aboutPro->data->rawData = rawData;

    return aboutPro;
}

void printAboutProPageNormalContent()
{
    printf(ABOUT_PROJECT_NORMAL_CONTENT);
}

void printAboutProPageEasterEgg1Content()
{
    printf(ABOUT_PROJECT_EASTER_EGG_1_CONTENT);
}

void printAboutProPageEasterEgg2Content()
{
    printf(ABOUT_PROJECT_EASTER_EGG_2_CONTENT);
}

PageOptionID getValidAboutProPageOptionFromUser()
{
    char c;

get_user_input:
    if ((c = (char)getchar()) != '\n') clearInputBuffer();
    switch (c)
    {
        // Quit
        case 'q':
        case 'Q':
            return ABOUTPRO_PAGE_OPTION_ID_PREVIOUS;
        // Easter egg 1
        case 'c':
        case 'C':
            return ABOUTPRO_PAGE_OPTION_ID_EASTEREGG1;
        // Easter egg 2
        case 't':
        case 'T':
            return ABOUTPRO_PAGE_OPTION_ID_EASTEREGG2;
        default:
        {
            printWithDoubleBuffer(
                printf("Enter 'q' or 'Q' to quit, though you can also enter 'a' or 'B'.\n");
                printf(PROMPT);
            );
            goto get_user_input;
        }
    }
}

void displayAboutProPage(PageData* data)
{
    AboutProPageData* aboutProData = (AboutProPageData*)data->rawData;

    clearAndPrintWithDoubleBuffer(
        printf(HOME_PAGE_DASHBOARD_FRAME);
        printf("\n\n");

        switch (aboutProData->selectedOption)
        {
            case ABOUTPRO_PAGE_OPTION_ID_NORMAL:
            {
                printAboutProPageNormalContent();
                break;
            }
            case ABOUTPRO_PAGE_OPTION_ID_EASTEREGG1:
            {
                printAboutProPageEasterEgg1Content();
                break;
            }
            case ABOUTPRO_PAGE_OPTION_ID_EASTEREGG2:
            {
                printAboutProPageEasterEgg2Content();
                break;
            }
            default:
            {
                printf("Unknown option for showing content of this page.");
                break;
            }
        }

        printf("\n");
        printf(PROMPT);
    );
}

Route* updateAboutProPage(PageData* data, Route* routePassByAboutPro)
{
    AboutProPageData* aboutProData = (AboutProPageData*)data->rawData;

    aboutProData->selectedOption = getValidAboutProPageOptionFromUser();

    switch (aboutProData->selectedOption)
    {
        case ABOUTPRO_PAGE_OPTION_ID_NORMAL:
        {
            routePassByAboutPro->status = ROUTE_OVER;
            routePassByAboutPro->exitStatus = ROUTE_EXIT_SUCCESS;
            return routePassByAboutPro;
        }
        case ABOUTPRO_PAGE_OPTION_ID_EASTEREGG1:
        case ABOUTPRO_PAGE_OPTION_ID_EASTEREGG2:
        {
            routePassByAboutPro->status = ROUTE_CONTINUE;
            return routePassByAboutPro;
        }
        default:
        {
            routePassByAboutPro->status = ROUTE_OVER;
            routePassByAboutPro->exitStatus = ROUTE_EXIT_FAILURE;
            return routePassByAboutPro;
        }
    }
}

void releaseAboutProPage(PageData** data)
{
    AboutProPageData* aboutProData = (AboutProPageData*)((*data)->rawData);
    free(aboutProData);
    free(*data);
    *data = NULL;
}