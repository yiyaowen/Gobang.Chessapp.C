#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CheData.h"
#include "CheDef.h"
#include "CheGlobal.h"
#include "CheTUI.h"
INCLUDE_DOUBLE_BUFFER

#include "Core.h"

//////////////
// Game TUI //
//////////////

Route *HandleGamePage(Route *route, PageInfo info_)
{
    GamePageInfo info = (GamePageInfo)info_;
    switch (info->game_prefab_config.mode)
    {
    case GPC_MODE_PVP:
        route = StartPvP(route, info->game_prefab_config);
        break;

    case GPC_MODE_PVC:
        route = StartPvC(route, info->game_prefab_config);
        break;
    
    default:
        route->status = ROUTE_OVER;
        route->exit_status = ROUTE_FAILURE;
        break;
    }
    return route;
}

Route *StartPvP(Route *route, GAME_PREFAB_CONFIG game_prefab_config)
{
    int iTotalRound = 0;
    int iGameResult;
    POSITION pos;
    POSITION lastPos;

    InitBoardArray();
    InitRecordBoardArray();
    InitPos(pos);
    InitPos(lastPos);

    autodisplay(DisplayBoard(pos));

    while (1) 
    {
        ////////////////////
        /* Round of Black */
        ////////////////////
        do {

            pos = GetValidPositionFromUser(ROUND_BLACK, pos); 
            if (pos.status == POS_QUIT) {
                route->status = ROUTE_OVER;
                route->exit_status = ROUTE_SUCCESS;
                return route;
            }

            autodisplay(DisplayBoard(pos));

        } while (pos.status == POS_PENDING);

        ++iTotalRound;
        UpdateGlobalBoardArrays(iTotalRound, ROUND_BLACK, lastPos, pos);
        lastPos = pos;
        autodisplay(DisplayBoard(pos));

        iGameResult = GetGameResult(RECORD_BLACK);
        if (iGameResult == GR_WIN) {
            // TODO
            printf("BLACK WIN\n");
            exit(0);
        }

        ////////////////////
        /* Round of White */
        ////////////////////
        do {
        
            pos = GetValidPositionFromUser(ROUND_WHITE, pos);
            if (pos.status == POS_QUIT) {
                route->status = ROUTE_OVER;
                route->exit_status = ROUTE_SUCCESS;
                return route;
            }

            autodisplay(DisplayBoard(pos));

        } while (pos.status == POS_PENDING);

        ++iTotalRound;
        UpdateGlobalBoardArrays(iTotalRound, ROUND_WHITE, lastPos, pos);
        lastPos = pos;
        autodisplay(DisplayBoard(pos));

        iGameResult = GetGameResult(RECORD_WHITE);
        if (iGameResult == GR_WIN) {
            // TODO
            printf("WHITE WIN\n");
            exit(0);
        }
    }   
    route->status = ROUTE_OVER;
    route->exit_status = ROUTE_FAILURE;
    return route;
}

Route *StartPvC(Route *route, GAME_PREFAB_CONFIG game_prefab_config)
{
    int iTotalRound = 0;
    int iGameResult;
    POSITION pos;
    POSITION lastPos;
    bool fPlayerFirst = (game_prefab_config.order == GPC_ORDER_PLAYER) ? true : false;

    InitBoardArray();
    InitRecordBoardArray();
    InitPos(pos);
    InitPos(lastPos);

    autodisplay(DisplayBoard(pos));

    while (1)
    {
        ////////////////////
        /* Round of Black */
        ////////////////////
        do {

            if (fPlayerFirst) {
                pos = GetValidPositionFromUser(ROUND_BLACK, pos);
            }
            else {
                CorePrefabConfig prefabConfig = {
                    CPC_SIDE_BLACK, // iSide
                    CPC_LEVEL_DRUNK // iLevel
                };
                CorePoint point = getCorePoint(RecordBoard, &prefabConfig);
                pos.x = Idx_iToPos_x(point.i);
                pos.y = Idx_jToPos_y(point.j);
                pos.status = POS_VERIFIED;
            }
            if (pos.status == POS_QUIT) {
                route->status = ROUTE_OVER;
                route->exit_status = ROUTE_SUCCESS;
                return route;
            }

            autodisplay(DisplayBoard(pos));

        } while (pos.status == POS_PENDING);

        ++iTotalRound;
        UpdateGlobalBoardArrays(iTotalRound, ROUND_BLACK, lastPos, pos);
        lastPos = pos;
        autodisplay(DisplayBoard(pos));

        iGameResult = GetGameResult(RECORD_BLACK);
        if (iGameResult == GR_WIN) {
            // TODO
            printf("BLACK WIN\n");
            exit(0);
        }

        ////////////////////
        /* Round of White */
        ////////////////////
        do {
        
            if (!fPlayerFirst) {
                pos = GetValidPositionFromUser(ROUND_WHITE, pos);
            }
            else {
                CorePrefabConfig prefabConfig = {
                    CPC_SIDE_WHITE, // iSide
                    CPC_LEVEL_DRUNK // iLevel
                };
                CorePoint point = getCorePoint(RecordBoard, &prefabConfig);
                pos.x = Idx_iToPos_x(point.i);
                pos.y = Idx_jToPos_y(point.j);
                pos.status = POS_VERIFIED;
            }
            if (pos.status == POS_QUIT) {
                route->status = ROUTE_OVER;
                route->exit_status = ROUTE_SUCCESS;
                return route;
            }

            autodisplay(DisplayBoard(pos));

        } while (pos.status == POS_PENDING);

        ++iTotalRound;
        UpdateGlobalBoardArrays(iTotalRound, ROUND_WHITE, lastPos, pos);
        lastPos = pos;
        autodisplay(DisplayBoard(pos));

        iGameResult = GetGameResult(RECORD_WHITE);
        if (iGameResult == GR_WIN) {
            // TODO
            printf("WHITE WIN\n");
            exit(0);
        }
    }
    route->status = ROUTE_OVER;
    route->exit_status = ROUTE_FAILURE;
    return route;
}

void PrintHint(int iRound)
{
    if (iRound == ROUND_BLACK) {
        printf("Black " BLACK_CIR_ICON "'s turn. ");
    }
    else if (iRound == ROUND_WHITE) {
        printf("White " WHITE_CIR_ICON "'s turn. ");
    }
    printf("Please input the position, e.g. 'A4'.");
    putchar('\n');
    printf(PROMPT);
}

POSITION GetValidPositionFromUser(int iRound, POSITION pos)
{
    char c;
    int iErrorType;
    int iScanResult;
    POSITION valid_pos = pos;

    autoprint(PrintHint(iRound));

get_user_input:
    c = getchar();
    if (IsSpecialControlOption(c)) {
        HandleControlOption(c, &valid_pos);
        return valid_pos;
    }
    else if (c == '\n') {
        PutCharBack(c);
        if (IsPositionValid(valid_pos) != POS_OVERLAPPED) {
            valid_pos.status = POS_VERIFIED;
            ClearInputBuffer();
            return valid_pos;
        }
        pos = valid_pos;
        iScanResult = 1;
    }
    else {
        pos.y = (c & 0x5f);
        iScanResult = scanf("%d", &pos.x);
        pos.status = POS_PENDING;
    }
    ClearInputBuffer();

    if ((iErrorType = IsPositionValid(pos)) != POS_VALID || iScanResult != 1) {
        if (iScanResult != 1) {
            iErrorType = POS_BAD_FORMAT;
        }
        autoprint(PrintErrorHint(iErrorType));
        goto get_user_input;
    }
    else {
        valid_pos = pos;
    }

    return valid_pos;
}

///////////////////
// PreAndSet TUI //
///////////////////

void InitPreAndSetPageInfo(PreAndSetPageInfo info)
{
    info->iOptionCount = OPTION_PreAndSet_NUM;
    info->iOptionSelected = OPTION_PreAndSet_Quit_NUM;
}

Page* GetDefaultPreAndSetPage()
{
    Page* pre_and_set_page = malloc(sizeof(Page));
    PreAndSetPageInfo pre_and_set_info = malloc(sizeof(PreAndSetPageInfoType));
    InitPreAndSetPageInfo(pre_and_set_info);
    pre_and_set_page->id = PAGE_ID_PreAndSet;
    pre_and_set_page->name = PAGE_NAME_PreAndSet;
    pre_and_set_page->desc = PAGE_DESC_PreAndSet;
    pre_and_set_page->info = pre_and_set_info;
    pre_and_set_page->pfnHandler = HandlePreAndSetPage;
    pre_and_set_page->pfnDisplayer = DisplayPreAndSetPage;
    return pre_and_set_page;
}

void DisplayPreAndSetPage(PageInfo info_)
{
    PreAndSetPageInfo info = (PreAndSetPageInfo)info_;

    printf(HOME_ICON);
    putchar('\n');
    putchar('\n');

    PrintPreAndSetOptions(info->iOptionSelected);

    printf(PROMPT);
}

void PrintPreAndSetOptions(int iOptionSelected)
{
    PrintPreAndSetOption(iOptionSelected, OPTION_PreAndSet_Quit_NUM, PREANDSET_OPTION_Quit);
    PrintPreAndSetOption(iOptionSelected, OPTION_PreAndSet_MusicSound_NUM, PREANDSET_OPTION_MusicSound);
    PrintPreAndSetOption(iOptionSelected, OPTION_PreAndSet_NetworkConfig_NUM, PREANDSET_OPTION_NetworkConfig);
}

void PrintPreAndSetOption(int iOptionSelected, int iOption, const char *szOptionText)
{
    PrintSpaces(20);
    if (iOptionSelected == iOption) {
        printf(BLUE_TEXT(HIGHLIGHT_TEXT(SELECT_ARROW)));
        PrintSpaces(2);
        printf(HIGHLIGHT_TEXT(UNDERLINE_TEXT("%s")), szOptionText);
    }
    else {
        PrintSpaces(5);
        printf("%s", szOptionText);
    }
    putchar('\n');
    putchar('\n');
}

Route *HandlePreAndSetPage(Route *route, PageInfo info_)
{
    PreAndSetPageInfo info = (PreAndSetPageInfo)info_;

    int iOption;     

    iOption = GetValidOptionFromUser(OPTION_PreAndSet_NUM, PREANDSET_OPTION_NUM);

    if (iOption == OPTION_Confirm_NUM) {

        Route* sub_route = GetDefaultRoute();

        switch (info->iOptionSelected)
        {
        case OPTION_PreAndSet_MusicSound_NUM:
            // TODO
            route->status = ROUTE_CONTINUE;
            return route;
            
        case OPTION_PreAndSet_NetworkConfig_NUM:
            // TODO
            route->status = ROUTE_CONTINUE;
            return route;

        case OPTION_PreAndSet_Quit_NUM:
            route->status = ROUTE_OVER;
            route->exit_status = ROUTE_SUCCESS;
            return route;

        default:
            route->status = ROUTE_OVER;
            route->exit_status = ROUTE_FAILURE;
            return route;
        }
        if (sub_route->exit_status == ROUTE_FAILURE) {
            route->status = ROUTE_OVER;
            route->exit_status = ROUTE_FAILURE;
        }
    }
    else {
        info->iOptionSelected = iOption;
        route->status = ROUTE_CONTINUE;
    }
    return route;
}

//////////////////
// AboutChe TUI //
//////////////////

void InitAboutChePageInfo(AboutChePageInfo info_)
{
    // Reserved
}

Route *HandleAboutChePage(Route *route, PageInfo info_)
{
    AboutChePageInfo info = (AboutChePageInfo)info_;

    char c;
    
get_user_input:
    if ((c = getchar()) != '\n') {
        ClearInputBuffer();
    }

    if (c == 'q' || c == 'Q') {
        route->status = ROUTE_OVER;
        route->exit_status = ROUTE_SUCCESS;
        return route;
    }
    else {
        autoprint(
            printf("Enter 'q' or 'Q' to quit.");
            putchar('\n');
            printf(PROMPT);
        );
        goto get_user_input;
    }
}

void PrintAboutCheContent()
{
    printf(ABOUT_CHESSPLAYER_CONTENT);
}
