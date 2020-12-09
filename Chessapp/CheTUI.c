#include <stdio.h>
#include <string.h>
#include <stdbool.h> // bool

#include "CheData.h"
#include "CheDef.h"
#include "CheGlobal.h"
#include "CheTUI.h"
INCLUDE_DOUBLE_BUFFER

#include "Cor.h" // GetCoreAnalysisResultP

extern HOME_OPTIONS HomeOptions;
extern int CurrentOptionNum;

extern DEFAULT_FLAT_BOARD Board;
extern GAME_RECORD_BOARD RecordBoard;

//////////////
// Home TUI //
//////////////

void SwitchToSelectedHomeOption()
{
    int iOptionResult;

    if (CurrentOptionNum < 0) {

        CurrentOptionNum = -CurrentOptionNum;

        switch (CurrentOptionNum)
        {
        case OPTION_PvP_NUM:
        {
            GAME_PREFAB_CONFIG game_prefab_config = {
                GPC_MODE_PVP,   // mode
                GPC_NULL,       // order
                GPC_NULL        // level
            };
            iOptionResult = StartPvP(game_prefab_config);
            break;
        }
            
        case OPTION_PvC_NUM:
        {
            // TODO
            GAME_PREFAB_CONFIG game_prefab_config = {
                GPC_MODE_PVC,   // mode
                GPC_NULL,       // order
                GPC_NULL        // level
            };
            iOptionResult = StartPvC(game_prefab_config);
            break;
        }

        case OPTION_PreAndSet_NUM:
            // TODO
            iOptionResult = StartPreAndSet();
            break;

        case OPTION_AboutChe_NUM:
            // TODO
            iOptionResult = StartAboutChe();
            break;

        case OPTION_AboutPro_NUM:
            // TODO
            iOptionResult = StartAboutPro();
            break;

        case OPTION_Exit_NUM:
            printf(GREEN_TEXT(HIGHLIGHT_TEXT("Bye ")) HIGHLIGHT_TEXT("EXIT_SUCCESS"));
            putchar('\n');
            exit(EXIT_SUCCESS);

error_abort:
        default:
            printf(RED_TEXT(HIGHLIGHT_TEXT("Error ")) HIGHLIGHT_TEXT("EXIT_FAILURE"));
            putchar('\n');
            exit(EXIT_FAILURE);
        }

        if (iOptionResult == OPT_QUIT) {
            return;
        }
        else if (iOptionResult == OPT_ABORT) {
            goto error_abort;
        }
    }
}


void DisplayHomePage()
{
    printf(HOME_ICON);
    putchar('\n');
    putchar('\n');

    PrintHomeOptions();

    printf(PROMPT);
}

void PrintHomeOptions()
{
    for (int i = 0; i < HOME_OPTION_NUM; ++i) {

        PrintSpaces(20);
        
        if (i+1 == CurrentOptionNum) {

            printf(BLUE_TEXT(HIGHLIGHT_TEXT(SELECT_ARROW)));
            PrintSpaces(2);

            if (i+1 == OPTION_Exit_NUM) {
                printf(RED_TEXT(HIGHLIGHT_TEXT(UNDERLINE_TEXT("%s"))), HomeOptions[i]);
            }
            else {
                printf(HIGHLIGHT_TEXT(UNDERLINE_TEXT("%s")), HomeOptions[i]);
            }
        } 
        else {

            PrintSpaces(5);
            printf("%s", HomeOptions[i]);
        }
        putchar('\n');
        putchar('\n');
    }
}

void GetValidHomeOption()
{
    char c;
    int iOption;
    
get_user_input:
    c = getchar();
    if (c == '\n') {
        PutCharBack(c);
        CurrentOptionNum = -CurrentOptionNum;
        ClearInputBuffer();
        return;
    }
    else {
        iOption = (int) (c - '0');
        if (IsHomeOptionValid(iOption)) {
            CurrentOptionNum = iOption;
            ClearInputBuffer();
            return;
        }
        else {
            autoprint(
                printf("No such option. Please choose from 1~%d, or press Enter.", HOME_OPTION_NUM);
                putchar('\n');
                printf(PROMPT);
            );
            ClearInputBuffer();
            goto get_user_input;
        }
    }
}

int IsHomeOptionValid(int iOptionNum)
{
    if (iOptionNum > 0 && iOptionNum <= HOME_OPTION_NUM) {
        return 1;
    }
    else {
        return 0;
    }
}

///////////////
// Board TUI //
///////////////

void DisplayBoard(POSITION pos) 
{	
    int i, j;
    char row;
    char col;

    for(j = 0, row = 15; j <= BOARD_SIZE - 1; j++) {

        // Display left infoboard
    
        if (j == 0) {
            printf(GAME_INFO_FRAME_TOP);
        }
        else {
            printf(GAME_INFO_FRAME_MIDDLE);
        }
        PrintSpaces(2);

        // Display chessboard
    
        if (row == pos.x) {
            printf(RED_TEXT(HIGHLIGHT_TEXT("%2d ")), row);
        }
        else {
            printf("%2d ", row);
        }
        row -= 1;

        for (i = 0; i <= BOARD_SIZE - 1; i++) {

            switch(Board[j][i])
            {
            case GRID_LEFT_TOP:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(LEFT_TOP_ICON)));
                }
                else {
                    printf(LEFT_TOP_ICON);
                }
                break;
				
            case GRID_RIGHT_TOP:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(RIGHT_TOP_ICON)));
                }
                else {
                    printf(RIGHT_TOP_ICON);
                }
                break;
				
            case GRID_RIGHT_BOTTOM:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(RIGHT_BOTTOM_ICON)));
                }
                else {
                    printf(RIGHT_BOTTOM_ICON);
                }
				break;
				
            case GRID_LEFT_BOTTOM:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(LEFT_BOTTOM_ICON)));
                }
                else {
                    printf(LEFT_BOTTOM_ICON);
                }
                break;
				
            case GRID_LEFT:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(LEFT_ICON)));
                }
                else {
                    printf(LEFT_ICON);
                }
                break;
				    
                case GRID_TOP:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(TOP_ICON)));
                }
                else {
                    printf(TOP_ICON);
                }
                break;
				
			case GRID_RIGHT:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(RIGHT_ICON)));
                }
                else {
                    printf(RIGHT_ICON);
                }
                break;
				
            case GRID_BOTTOM:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(BOTTOM_ICON)));
                }
                else {
                    printf(BOTTOM_ICON);
                }
                break;
				
            case GRID_MIDDLE:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT(MIDDLE_ICON)));
                }
                else if ((j == (BOARD_SIZE - 4) && i == ('D' - 'A')) ||
                         (j == (BOARD_SIZE - 4) && i == ('L' - 'A')) ||
                         (j == (BOARD_SIZE - 12) && i == ('D' - 'A')) ||
                         (j == (BOARD_SIZE - 12) && i == ('L' - 'A')) ||
                         (j == (BOARD_SIZE - 8) && i == ('H' - 'A')))
                {
                    printf(HIGHLIGHT_TEXT(MIDDLE_ICON));
                }
                else {
                    printf(MIDDLE_ICON);
                }
                break;
				
            case BLACK_TRI:      
                printf(BLACK_TRI_ICON);
                break;
				
            case WHITE_TRI:      
                printf(WHITE_TRI_ICON);
                break;
				
            case BLACK_CIR:      
                printf(BLACK_CIR_ICON);
                break;
            
            case WHITE_CIR:
                printf(WHITE_CIR_ICON);
                break;
            }
        }

        // Display right infoboard
    
        PrintSpaces(1);
        if (j == 0) {
            printf(GAME_INFO_FRAME_TOP);
        }
        else {
            printf(GAME_INFO_FRAME_MIDDLE);
        }

        putchar('\n');

    }

    // Display last row

    printf(GAME_INFO_FRAME_BOTTOM);
    PrintSpaces(2);
	
    printf("   ");
    for (col = 'A'; col < 'A' + BOARD_SIZE ; col++) {
        if (col == pos.y) {
            printf(RED_TEXT(HIGHLIGHT_TEXT("%c ")),col);
        }
        else {
            printf("%c ", col);
        }
    }

    PrintSpaces(1);
    printf(GAME_INFO_FRAME_BOTTOM);

    // Go to new line
	
    putchar('\n');
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

POSITION GetValidPosition(int iRound, POSITION pos)
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

int IsSpecialControlOption(char key)
{
    if (key == 'q' || key == 'Q' ||
        key == 's' || key == 'S' ||
        key == 'v' || key == 'V') {
        return 1;
    }
    else {
        return 0;
    }
}

void HandleControlOption(char key, POSITION *inPos)
{
    switch (key)
    {
    // Quit
    case 'q':
    case 'Q':
        inPos->status = POS_QUIT;
        ClearInputBuffer();
        return;

    // Save
    case 's':
    case 'S':
    { // Need brace here, otherwise compile failed with [clang-1200.0.32.27]
        char path[80];
        int iReadPathResult;

        inPos->status = POS_PENDING;

        autoprint(
            printf("Save game record to file. Please input target file path.");
            putchar('\n');
            printf("File path: ");
        );

        iReadPathResult = scanf("%s", path); 
        ClearInputBuffer();
        if (iReadPathResult != 1) {
            autoprint(
                printf(HIGHLIGHT_TEXT(RED_TEXT("Can't read target file path."))
                    " Press enter to back to game. " HIGHLIGHT_TEXT("[Enter]"));
            );
            ClearInputBuffer();
            return;
        }

        if (!ExportBoardToFile(RecordBoard, path)) {
            autoprint(
                printf("Invalid target file path. Please make sure recursive directories exist.");
                putchar('\n');
                printf("Target file will be created if not exists. Try to check related permissions.");
                putchar('\n');
                printf(HIGHLIGHT_TEXT(RED_TEXT("Can't write target file."))
                       " Press enter to back to game." HIGHLIGHT_TEXT("[Enter]"));
            );
            ClearInputBuffer();
            return;
        }

        autoprint(
            printf("Target file %s saved successfully. Press enter to continue. "
               HIGHLIGHT_TEXT("[Enter]"), path);
        );
        ClearInputBuffer();
        return;
    }
        
    default:
        return;
    }
}
        

int IsPositionValid(POSITION pos)
{
    if (!('A' <= pos.y && pos.y <= 'O' && 1 <= pos.x && pos.x <= 15)) {
        return POS_OUT_OF_BOARD;
    }
    else if (Board[BOARD_SIZE-pos.x][pos.y-'A'] == BLACK_CIR ||
             Board[BOARD_SIZE-pos.x][pos.y-'A'] == BLACK_TRI ||
             Board[BOARD_SIZE-pos.x][pos.y-'A'] == WHITE_CIR ||
             Board[BOARD_SIZE-pos.x][pos.y-'A'] == WHITE_TRI) {
        return POS_OVERLAPPED;
    } 
    else {
        return POS_VALID;
    }
}
    
void PrintErrorHint(int iErrorType)
{
    switch (iErrorType)
    {
    case POS_OUT_OF_BOARD:
        printf("Position is out of the chessboard. Valid range: A~O & 1~15");
        putchar('\n');
        break;

    case POS_OVERLAPPED:
        printf("The position is occupied. Please choose another position.");
        putchar('\n');
        break;

    case POS_BAD_FORMAT:
        printf("Bad position format. Please input a letter followed by a number.");
        putchar('\n');
        break;

    default:
        printf("An unknown error occurred.");
        putchar('\n');
        break;
    }
    printf(PROMPT);
}

int StartPvP(GAME_PREFAB_CONFIG game_prefab_config)
{
    int iTotalRound = 0;
    int iGameResult;
    POSITION pos;
    POSITION lastPos;

    InitBoardArray();
    InitRecordBoardArray();
    InitPos(pos);

    autodisplay(DisplayBoard(pos));

    while (1) 
    {
        ////////////////////
        /* Round of Black */
        ////////////////////
        do {

            pos = GetValidPosition(ROUND_BLACK, pos); 
            if (pos.status == POS_QUIT) {
                return OPT_QUIT;
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
        
            pos = GetValidPosition(ROUND_WHITE, pos);
            if (pos.status == POS_QUIT) {
                return OPT_QUIT;
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

    return OPT_ABORT;
}

int StartPvC(GAME_PREFAB_CONFIG game_prefab_config)
{
    int iTotalRound = 0;
    int iGameResult;
    POSITION pos;
    POSITION lastPos;
    bool fPlayerFirst = (game_prefab_config.order == GPC_ORDER_PLAYER) ? true : false;

    InitBoardArray();
    InitRecordBoardArray();
    InitPos(pos);

    autodisplay(DisplayBoard(pos));

    while (1)
    {
        ////////////////////
        /* Round of Black */
        ////////////////////
        do {

            if (fPlayerFirst) {
                pos = GetValidPosition(ROUND_BLACK, pos);
            }
            else {
                ANALYSIS_PREFAB_CONFIG analysis_prefb_config = {
                    APC_SIDE_BLACK, // iSide
                    APC_LEVEL_DRUNK // iLevel
                };
                COR_POSITION cor_pos = GetCoreAnalysisResultP(RecordBoard, analysis_prefb_config);
                pos.x = cor_pos.x;
                pos.y = cor_pos.y;
                pos.status = POS_VERIFIED;
            }
            if (pos.status == POS_QUIT) {
                return OPT_QUIT;
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
                pos = GetValidPosition(ROUND_WHITE, pos);
            }
            else {
                ANALYSIS_PREFAB_CONFIG analysis_prefb_config = {
                    APC_SIDE_WHITE, // iSide
                    APC_LEVEL_DRUNK // iLevel
                };
                COR_POSITION cor_pos = GetCoreAnalysisResultP(RecordBoard, analysis_prefb_config);
                pos.x = cor_pos.x;
                pos.y = cor_pos.y;
                pos.status = POS_VERIFIED;
            }
            if (pos.status == POS_QUIT) {
                return OPT_QUIT;
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

    return OPT_ABORT;
}

void DisplayPreAndSetPage(int iOption)
{
    printf(HOME_ICON);
    putchar('\n');
    putchar('\n');

    PrintPreAndSetOptions(iOption);

    printf(PROMPT);
}

void PrintPreAndSetOptions(int iOption)
{
    PrintPreAndSetOption(iOption, OPTION_PreAndSet_Quit_NUM, PREANDSET_OPTION_Quit);
    PrintPreAndSetOption(iOption, OPTION_PreAndSet_MusicSound_NUM, PREANDSET_OPTION_MusicSound);
    PrintPreAndSetOption(iOption, OPTION_PreAndSet_NetworkConfig_NUM, PREANDSET_OPTION_NetworkConfig);
}

void PrintPreAndSetOption(int iOption, int iOptionNum, const char *szOptionText)
{
    PrintSpaces(20);
    if (iOption == iOptionNum) {
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

int GetValidPreAndSetOption()
{
    char c;
    int iOption;
    
get_user_input:
    c = getchar();
    if (c == '\n') {
        PutCharBack(c);
        ClearInputBuffer();
        return OPTION_PreAndSet_Confirm_NUM;
    }
    else {
        iOption = (int) (c - '0');
        if (IsPreAndSetOptionValid(iOption)) {
            ClearInputBuffer();
            return iOption+OPTION_PreAndSet_NUM*10;
        }
        else {
            autoprint(
                printf("No such option. Please choose from 1~%d, or press Enter.", PREANDSET_OPTION_NUM);
                putchar('\n');
                printf(PROMPT);
            );
            ClearInputBuffer();
            goto get_user_input;
        }
    }
}

int IsPreAndSetOptionValid(int iOption)
{
    if (iOption > 0 && iOption <= PREANDSET_OPTION_NUM) {
        return 1;
    }
    else {
        return 0;
    }
}

void SwitchToSelectedPreAndSetOption(int iOption)
{
    // TODO
}

int StartPreAndSet()
{
    int iOption, iOptionSelected;
    iOption = iOptionSelected = OPTION_PreAndSet_Quit_NUM;

get_user_input:
    autodisplay(DisplayPreAndSetPage(iOptionSelected));

    iOption = GetValidPreAndSetOption();

    if (iOption == OPTION_PreAndSet_Confirm_NUM) {

        switch (iOptionSelected)
        {
        case OPTION_PreAndSet_MusicSound_NUM:
        {
            // TODO
            goto get_user_input;
        }
            
        case OPTION_PreAndSet_NetworkConfig_NUM:
        {
            // TODO
            goto get_user_input;
        }

        case OPTION_PreAndSet_Quit_NUM:
        {
            // TODO
            return OPT_QUIT;
        }

error_abort:
        default:
            printf(RED_TEXT(HIGHLIGHT_TEXT("Error ")) HIGHLIGHT_TEXT("EXIT_FAILURE"));
            putchar('\n');
            exit(EXIT_FAILURE);
        }
    }
    else {
        iOptionSelected = iOption;
        goto get_user_input;
    }
    
    return OPT_ABORT;
}

void DisplayAboutProPage(int iOption)
{
    printf(HOME_ICON);
    putchar('\n');
    putchar('\n');

    switch (iOption)
    {
    case OPTION_AboutPro_NUM:
        PrintAboutProContent();
        putchar('\n');
        break;
    
    case OPTION_AboutPro_EasterEgg1_NUM:
        PrintAboutProEasterEgg1Content();
        putchar('\n');
        break;

    case OPTION_AboutPro_EasterEgg2_NUM:
        PrintAboutProEasterEgg2Content();
        putchar('\n');
        break;

    default:
        printf("Unknown option for showing content of this page.");
        putchar('\n');
        break;
    }

    printf(PROMPT);
}

void PrintAboutProContent()
{
    printf(ABOUT_PROJECT_CONTENT);
}

void PrintAboutProEasterEgg1Content()
{
    printf(ABOUT_PROJECT_EASTER_EGG_1_CONTENT);
}

void PrintAboutProEasterEgg2Content()
{
    printf(ABOUT_PROJECT_EASTER_EGG_2_CONTENT);
}

int GetValidAboutProOption()
{
    char c;
    
get_user_input:
    if ((c = getchar()) != '\n') {
        ClearInputBuffer();
    }
    switch (c)
    {
    // Quit
    case 'q':
    case 'Q':
        return OPTION_AboutPro_Quit_NUM;
    
    // Egg1
    case 'c':
    case 'C':
        return OPTION_AboutPro_EasterEgg1_NUM;

    // Egg2
    case 't':
    case 'T':
        return OPTION_AboutPro_EasterEgg2_NUM;

    default:
        printf("Enter 'q' or 'Q' to quit, though you can also enter 'a' or 'B'.");
        putchar('\n');
        printf(PROMPT);
        goto get_user_input;
    }
}

int StartAboutPro()
{
    int iOption;

    autodisplay(DisplayAboutProPage(OPTION_AboutPro_NUM));
    
get_user_input:
    iOption = GetValidAboutProOption();

    switch (iOption)
    {
    case OPTION_AboutPro_Quit_NUM:
        return OPT_QUIT;

    case OPTION_AboutPro_EasterEgg1_NUM:
        autodisplay(DisplayAboutProPage(OPTION_AboutPro_EasterEgg1_NUM));
        goto get_user_input;

    case OPTION_AboutPro_EasterEgg2_NUM:
        autodisplay(DisplayAboutProPage(OPTION_AboutPro_EasterEgg2_NUM));
        goto get_user_input;

    default:
        printf("Unknow option for 'About Project' page.");
        putchar('\n');
        return OPT_ABORT;
    }
}

void DisplayAboutChePage()
{
    printf(HOME_ICON);
    putchar('\n');
    putchar('\n');

    PrintAboutCheContent();
    putchar('\n');

    printf(PROMPT);
}

void PrintAboutCheContent()
{
    printf(ABOUT_CHESSPLAYER_CONTENT);
}

int StartAboutChe()
{
    char c;

    autodisplay(DisplayAboutChePage());
    
get_user_input:
    if ((c = getchar()) != '\n') {
        ClearInputBuffer();
    }

    if (c == 'q' || c == 'Q') {
        return OPT_QUIT;
    }
    else {
        printf("Enter 'q' or 'Q' to quit.");
        putchar('\n');
        printf(PROMPT);
        goto get_user_input;
    }
}
