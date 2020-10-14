#include <stdio.h> 
#include <stdlib.h>

#include "CheTUI.h"
#include "CheGlobal.h"

extern HOME_OPTIONS HomeOptions;
extern int SelectedHomeOption;

extern DEFAULT_FLAT_BOARD Board;
extern DEFAULT_FLAT_POSITION Pos;

//////////////
// Home TUI //
//////////////
void DisplayHomeOptions()
{
    for (int i = 0; i < HOME_OPTION_NUM; ++i) {

        PrintSpaces(20);
        
        if (i+1 == SelectedHomeOption) {

            printf(BLUE_TEXT(BLINK_TEXT(HIGHLIGHT_TEXT(SELECT_ARROW))));
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

    printf(HOME_ICON);
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
        SelectedHomeOption = -SelectedHomeOption;
        return;
    }
    else {
        iOption = (int) (c - '0');
        SelectedHomeOption = (iOption > 0 && iOption <= HOME_OPTION_NUM) ? 
                              iOption : SelectedHomeOption;
    }
    ClearInputBuffer();

    while (!IsOptionValid(iOption)) {

        printf("没有这个选项. 请从 1~%d 中选择, 或者按下回车键确认.\n", HOME_OPTION_NUM);
        printf(PROMPT);

        c = getchar();
        if (c == '\n') {
            SelectedHomeOption = -SelectedHomeOption;
            return;
        }
        else {
            iOption = (int) (c - '0');
            SelectedHomeOption = (iOption > 0 && iOption <= HOME_OPTION_NUM) ? 
                                  iOption : SelectedHomeOption;
        }
        ClearInputBuffer();
    }
}

int IsOptionValid(int iOption)
{
    if (iOption > 0 && iOption <= HOME_OPTION_NUM) {
        return 1;
    }
    else {
        return 0;
    }
}

void SwitchToSelectedOption()
{
    int iOptionResult;

    if (SelectedHomeOption < 0) {

        SelectedHomeOption = -SelectedHomeOption;

        switch (SelectedHomeOption)
        {
        case OPTION_PvP_NUM:
            iOptionResult = StartPvP();
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
            ClearScreen();
            exit(0);
            break;

        default:
            DisplayHome();
            break;
        }
    }
    else {
        DisplayHome();
    }
}

///////////////
// Board TUI //
///////////////
void DisplayBoard() 
{	
	int i, j;
	char row;
	char col;

    ClearScreen();
	
	for(j = 0,row = 15; j <= BOARD_SIZE - 1; j++) {

        if (row == Pos.x) {
            printf(RED_TEXT(HIGHLIGHT_TEXT("%2d ")),row);
        }
        else {
            printf("%2d ", row);
        }
		row -= 1;

		for(i = 0; i <= BOARD_SIZE - 1; i++) {

			switch(Board[j][i])
			{
			case 1:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┏ ")));
                }
                else {
                    printf("┏ ");
                }
				break;
				
			case 2:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┓ ")));
                }
                else {
                    printf("┓ ");
                }
				break;
				
			case 3:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┛ ")));
                }
                else {
                    printf("┛ ");
                }
				break;
				
			case 4:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┗ ")));
                }
                else {
                    printf("┗ ");
                }
				break;
				
			case 5:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┠ ")));
                }
                else {
                    printf("┠ ");
                }
				break;
				
			case 6:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┯ ")));
                }
                else {
                    printf("┯ ");
                }
				break;
				
			case 7:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┨ ")));
                }
                else {
                    printf("┨ ");
                }
				break;
				
			case 8:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┷ ")));
                }
                else {
                    printf("┷ ");
                }
				break;
				
			case 9:
                if (j == (BOARD_SIZE - Pos.x) && i == (Pos.y - 'A')) {
                    printf(RED_TEXT(HIGHLIGHT_TEXT("┼ ")));
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
	}
	
	printf("   ");
	for (col = 'A'; col < 'A' + BOARD_SIZE ; col++) {
        if (col == Pos.y) {
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

void GetValidPosition(int iRound)
{
    char c;
    POSITION tmpPos;
    int iErrorType;
    int iScanResult;

    DisplayHint(iRound);
    c = getchar();
    if (c == '\n') {
        if (IsPositionValid(Pos) != POS_OVERLAPPED) {
            Pos.status = POS_VERIFIED;
            return;
        }
        tmpPos = Pos;
        iScanResult = 1;
    }
    else {
        tmpPos.y = (c & 0x5f);
        iScanResult = scanf("%d", &tmpPos.x);
        tmpPos.status = POS_PENDING;
    }
    ClearInputBuffer();

    while ((iErrorType = IsPositionValid(tmpPos)) != POS_VALID || iScanResult != 1) {

        if (iScanResult != 1) {
            iErrorType = POS_BAD_FORMAT;
        }

        DisplayErrorHint(iErrorType);
        c = getchar();
        if (c == '\n') {
            if (IsPositionValid(Pos) != POS_OVERLAPPED) {
                Pos.status = POS_VERIFIED;
                return;
            }
            tmpPos = Pos;
            iScanResult = 1;
        }
        else {
            tmpPos.y = (c & 0x5f);
            iScanResult = scanf("%d", &tmpPos.x);
            tmpPos.status = POS_PENDING;
        }
        ClearInputBuffer();
    }
    
    /* [tmpPos] here must be valid */
    Pos = tmpPos;
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
    POSITION lastPos;

    InitBoardArray();
    InitGlobalPos();

    DisplayBoard();

    while (1) 
    {   
        /* Round of Black */
        do {
            GetValidPosition(ROUND_BLACK); 
            DisplayBoard();
        } while (Pos.status == POS_PENDING);

        Board[BOARD_SIZE-Pos.x][Pos.y-'A'] = BLACK_TRI;
        if (iTotalRound) Board[BOARD_SIZE-lastPos.x][lastPos.y-'A'] = WHITE_CIR;
        lastPos = Pos;
        DisplayBoard(); 

        ++iTotalRound;

        /* Round of White */
        do {
            GetValidPosition(ROUND_WHITE);
            DisplayBoard();
        } while (Pos.status == POS_PENDING);

        Board[BOARD_SIZE-Pos.x][Pos.y-'A'] = WHITE_TRI;
        Board[BOARD_SIZE-lastPos.x][lastPos.y-'A'] = BLACK_CIR;
        lastPos = Pos;
        DisplayBoard();

        ++iTotalRound;
    }   

    return 0;
}
