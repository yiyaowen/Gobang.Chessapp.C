#include <stdio.h>

#include "CheDef.h"
#include "CheTUI.h"
#include "CheGlobal.h"

extern HOME_OPTIONS HomeOptions;
extern int CurrentOptionNum;

extern DEFAULT_FLAT_BOARD Board;

//////////////
// Home TUI //
//////////////

void DisplayHomeOptions()
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
    }
}

void DisplayHome()
{
    ClearScreen();

    BEGIN_ATTR(WHITE_B_ATTR);
    BEGIN_ATTR(HIGHLIGHT_ATTR);

    printf(HOME_ICON);

    END_ATTR();
    putchar('\n');

    DisplayHomeOptions();

    printf(PROMPT);
}

void GetValidHomeOption()
{
    char c;
    int iOption;
    
    c = getchar();
    if (c == '\n') {
        CurrentOptionNum = -CurrentOptionNum;
        return;
    }
    else {
        iOption = (int) (c - '0');
        CurrentOptionNum = (iOption > 0 && iOption <= HOME_OPTION_NUM) ? 
                              iOption : CurrentOptionNum;
    }
    ClearInputBuffer();

    while (!IsOptionValid(iOption)) {

        printf("没有这个选项. 请从 1~%d 中选择, 或者按下回车键确认.\n", HOME_OPTION_NUM);
        printf(PROMPT);

        c = getchar();
        if (c == '\n') {
            CurrentOptionNum = -CurrentOptionNum;
            return;
        }
        else {
            iOption = (int) (c - '0');
            CurrentOptionNum = (iOption > 0 && iOption <= HOME_OPTION_NUM) ? 
                                  iOption : CurrentOptionNum;
        }
        ClearInputBuffer();
    }
}

int IsOptionValid(int iOptionNum)
{
    if (iOptionNum > 0 && iOptionNum <= HOME_OPTION_NUM) {
        return 1;
    }
    else {
        return 0;
    }
}

void SwitchToSelectedOption()
{
    int iOptionResult;

    if (CurrentOptionNum < 0) {

        CurrentOptionNum = -CurrentOptionNum;

        switch (CurrentOptionNum)
        {
        case OPTION_PvP_NUM:

            iOptionResult = StartPvP();

            if (iOptionResult == OPT_QUIT) {
                return;
            }

            break;
            
        case OPTION_PvC_NUM:
            DisplayHome();
            // TODO
            break;

        case OPTION_PreAndSet_NUM:
            DisplayHome();
            // TODO
            break;

        case OPTION_AboutChe_NUM:
            DisplayHome();
            // TODO
            break;

        case OPTION_AboutPro_NUM:
            DisplayHome();
            // TODO
            break;

        case OPTION_Exit_NUM:
            printf(GREEN_TEXT(HIGHLIGHT_TEXT("Bye ")) HIGHLIGHT_TEXT("EXIT_SUCCESS\n"));
            exit(EXIT_SUCCESS);
            break;

        default:
            printf(RED_TEXT(HIGHLIGHT_TEXT("Error ")) HIGHLIGHT_TEXT("EXIT_FAILURE\n"));
            exit(EXIT_FAILURE);
            break;
        }
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

	for(j = 0,row = 15; j <= BOARD_SIZE - 1; j++) {

        if (row == pos.x) {
            printf(RED_TEXT(HIGHLIGHT_TEXT("%2d ")), row);
        }
        else {
            printf("%2d ", row);
        }
		row -= 1;

        BEGIN_ATTR(WHITE_B_ATTR);
		for(i = 0; i <= BOARD_SIZE - 1; i++) {

			switch(Board[j][i])
			{
			case 1:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┏ ")));
                }
                else {
                    printf("┏ ");
                }
				break;
				
			case 2:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┓")));
                }
                else {
                    printf("┓");
                }
				break;
				
			case 3:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┛")));
                }
                else {
                    printf("┛");
                }
				break;
				
			case 4:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┗ ")));
                }
                else {
                    printf("┗ ");
                }
				break;
				
			case 5:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┠ ")));
                }
                else {
                    printf("┠ ");
                }
				break;
				
			case 6:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┯ ")));
                }
                else {
                    printf("┯ ");
                }
				break;
				
			case 7:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┨")));
                }
                else {
                    printf("┨");
                }
				break;
				
			case 8:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┷ ")));
                }
                else {
                    printf("┷ ");
                }
				break;
				
			case 9:
                if (j == (BOARD_SIZE - pos.x) && i == (pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┼ ")));
                }
                else if ((j == (BOARD_SIZE - 4) && i == ('D' - 'A')) ||
                         (j == (BOARD_SIZE - 4) && i == ('L' - 'A')) ||
                         (j == (BOARD_SIZE - 12) && i == ('D' - 'A')) ||
                         (j == (BOARD_SIZE - 12) && i == ('L' - 'A')) ||
                         (j == (BOARD_SIZE - 8) && i == ('H' - 'A'))) {
                    printf(HIGHLIGHT_TEXT("┼ "));
                }
                else {
                    printf("┼ ");
                }
				break;
				
			case BLACK_TRI:      
				printf("▲ ");
				break;
				
			case WHITE_TRI:      
				printf("△ ");
				break;
				
			case BLACK_CIR:      
				printf("● ");
				break;
            
			case WHITE_CIR:
				printf("○ ");
				break;
			}

			if(i == BOARD_SIZE - 1) {
				printf("\n");
			}
		}

        END_ATTR();
	}
	
	printf("   ");
	for (col = 'A'; col < 'A' + BOARD_SIZE ; col++) {
        if (col == pos.y) {
            printf(RED_TEXT(HIGHLIGHT_TEXT("%c ")),col);
        }
        else {
            printf("%c ", col);
        }
    }
	
	printf("\n");
}

void DisplayHint(int iRound)
{
    if (iRound == ROUND_BLACK) {
        printf("黑棋● 的回合. ");
    }
    else if (iRound == ROUND_WHITE) {
        printf("白棋○ 的回合. ");
    }

    printf("请输入棋子的坐标, 例如: 'A4'.\n");
    printf(PROMPT);
}

POSITION GetValidPosition(int iRound, POSITION pos)
{
    char c;
    int iErrorType;
    int iScanResult;

    DisplayHint(iRound);
    c = getchar();
    if (c == 'q' || c == 'Q') {
        pos.status = POS_QUIT;
        ClearInputBuffer();
        return pos;
    }
    else if (c == '\n') {
        if (IsPositionValid(pos) != POS_OVERLAPPED) {
            pos.status = POS_VERIFIED;
            ClearInputBuffer();
            return pos;
        }
        iScanResult = 1;
    }
    else {
        pos.y = (c & 0x5f);
        iScanResult = scanf("%d", &pos.x);
        pos.status = POS_PENDING;
    }
    ClearInputBuffer();

    while ((iErrorType = IsPositionValid(pos)) != POS_VALID || iScanResult != 1) {

        if (iScanResult != 1) {
            iErrorType = POS_BAD_FORMAT;
        }

        DisplayErrorHint(iErrorType);
        c = getchar();
        if (c == 'q' || c == 'Q') {
            pos.status = POS_QUIT;
            ClearInputBuffer();
            return pos;
        }
        else if (c == '\n') {
            if (IsPositionValid(pos) != POS_OVERLAPPED) {
                pos.status = POS_VERIFIED;
                ClearInputBuffer();
                return pos;
            }
            iScanResult = 1;
        }
        else {
            pos.y = (c & 0x5f);
            iScanResult = scanf("%d", &pos.x);
            pos.status = POS_PENDING;
        }
        ClearInputBuffer();
    }

    return pos;
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
    
void DisplayErrorHint(int iErrorType)
{
    switch (iErrorType)
    {
    case POS_OUT_OF_BOARD:
        printf("坐标超出棋盘边界. 合法的坐标: A~O 和 1~15\n");
        break;

    case POS_OVERLAPPED:
        printf("该位置已有棋子. 请选择空位置落子.\n");
        break;

    case POS_BAD_FORMAT:
        printf("坐标格式错误. 请先输入一个字母，紧接着再输入一个数字.\n");
        break;

    default:
        printf("发生未知类型的错误.\n");
        break;
    }
    printf(PROMPT);
}

int StartPvP()
{
    int iTotalRound = 0;
    POSITION pos;
    POSITION lastPos;

    InitBoardArray();
    InitPos(pos);

    ClearScreen();
    DisplayBoard(pos);

    while (1) 
    {   
        // Round of Black
        do {

            pos = GetValidPosition(ROUND_BLACK, pos); 
            if (pos.status == POS_QUIT) {
                return OPT_QUIT;
            }

            ClearScreen();
            DisplayBoard(pos);

        } while (pos.status == POS_PENDING);

        Board[BOARD_SIZE-pos.x][pos.y-'A'] = BLACK_TRI;
        // Skip first round
        if (iTotalRound) Board[BOARD_SIZE-lastPos.x][lastPos.y-'A'] = WHITE_CIR;
        lastPos = pos;
        ClearScreen();
        DisplayBoard(pos); 

        ++iTotalRound;

        // Round of White
        do {
        
            pos = GetValidPosition(ROUND_WHITE, pos);
            if (pos.status == POS_QUIT) {
                return OPT_QUIT;
            }

            ClearScreen();
            DisplayBoard(pos);

        } while (pos.status == POS_PENDING);

        Board[BOARD_SIZE-pos.x][pos.y-'A'] = WHITE_TRI;
        Board[BOARD_SIZE-lastPos.x][lastPos.y-'A'] = BLACK_CIR;
        lastPos = pos;
        ClearScreen();
        DisplayBoard(pos);

        ++iTotalRound;
    }   

    return OPT_ABORT;
}
