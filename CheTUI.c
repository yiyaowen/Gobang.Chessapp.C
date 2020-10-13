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
void InitHomeOptionsArray()
{
    HomeOptions[0] = HOME_OPTION_1;
    HomeOptions[1] = HOME_OPTION_2;
    HomeOptions[2] = HOME_OPTION_3;
    HomeOptions[3] = HOME_OPTION_4;
    HomeOptions[4] = HOME_OPTION_5;
    HomeOptions[5] = HOME_OPTION_6;
}

void DisplayHomeOptions()
{
    for (int i = 0; i < HOME_OPTION_NUM; ++i) {
        printf("%s", HomeOptions[i]);
    }
}

void DisplayHome()
{
    ClearScreen();

    printf("%s", HOME_ICON);
    printf("%s", HOME_MESSAGE);
    InitHomeOptionsArray();
    DisplayHomeOptions();
    printf(PROMPT);
}

void GetValidHomeOption()
{
    scanf("%d", &SelectedHomeOption);
    ClearInputBuffer('\n');

    while (!IsHomeOptionValid()) {

        printf("没有这个选项. 请从 1~%d 中选择.\n", HOME_OPTION_NUM);
        printf(PROMPT);

        scanf("%d", &SelectedHomeOption);
        ClearInputBuffer('\n');
    }
}

int IsHomeOptionValid()
{
    if (SelectedHomeOption > 0 && SelectedHomeOption <= HOME_OPTION_NUM) {
        return 1;
    }
    else {
        return 0;
    }
}

void SwitchToSelectedOption()
{
    int iOptionResult;

    switch (SelectedHomeOption)
    {
    case 1:
        iOptionResult = StartPvP();
        break;
        
    case 2:
        DisplayHome();
        // TODO
        break;

    case 3:
        DisplayHome();
        // TODO
        break;

    case 4:
        DisplayHome();
        // TODO
        break;

    case 5:
        DisplayHome();
        // TODO
        break;

    case 6:
        DisplayHome();
        // TODO
        break;

    default:
        DisplayHome();
        break;
    }
}

///////////////
// Board TUI //
///////////////
void InitBoardArray()
{
    int i, j;
	
	Board[0][0] = 1;
	Board[0][BOARD_SIZE-1] = 2;
	Board[BOARD_SIZE-1][BOARD_SIZE-1] = 3;
	Board[BOARD_SIZE-1][0] = 4;
	
	for (j = 1; j <= BOARD_SIZE - 2; ++j) {
		Board[j][0] = 5;
	}
	
	for (i = 1; i <= BOARD_SIZE - 2; ++i) {
		Board[0][i] = 6;
	}
	
	for (j = 1; j <= BOARD_SIZE - 2; ++j) {
		Board[j][BOARD_SIZE - 1] = 7;
	}
	
	for (i = 1; i <= BOARD_SIZE - 2; ++i) {
		Board[BOARD_SIZE - 1][i] = 8;
	}
	
	for (j = 1; j <= BOARD_SIZE - 2; ++j) {
		for (i = 1; i <= BOARD_SIZE - 2; ++i) {
			Board[j][i] = 9;
		}
	}
}

void DisplayBoard() 
{	
	int i, j;
	char row;
	char col;

    ClearScreen();
	
	for(j = 0,row = 15; j <= BOARD_SIZE - 1; j++) {

		printf("%2d ",row);
		row -= 1;

		for(i = 0; i <= BOARD_SIZE - 1; i++) {

			switch(Board[j][i])
			{
			case 1:
				printf("┏ ");
				break;
				
			case 2:
				printf("┓ ");
				break;
				
			case 3:
				printf("┛ ");
				break;
				
			case 4:
				printf("┗ ");
				break;
				
			case 5:
				printf("┠ ");
				break;
				
			case 6:
				printf("┯ ");
				break;
				
			case 7:
				printf("┨ ");
				break;
				
			case 8:
				printf("┷ ");
				break;
				
			case 9:
				printf("┼ ");
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
		printf("%c ",col);
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
    printf("坐标: ");
}

void GetValidPosition(int iRound)
{
    int iScanResult;

    DisplayHint(iRound);
    iScanResult = scanf("%c%d", &Pos.y, &Pos.x);
    ClearInputBuffer('\n');

    while (1) {

        int iErrorType;
        if (iScanResult != 2) {
            iErrorType = POS_BAD_FORMAT;
        }
        else {
            iErrorType = IsPositionValid();
        }

        if (iErrorType != POS_VALID) {
            DisplayErrorHint(iErrorType);
            iScanResult = scanf("%c%d", &Pos.y, &Pos.x); 
            ClearInputBuffer('\n');
        }
        else {
            break;
        }
    }
}

int IsPositionValid()
{
    if (!('A' <= (Pos.y &= 0x5f)  && Pos.y <= 'O' && 1 <= Pos.x && Pos.x <= 15)) {
        return POS_OUT_OF_BOARD;
    }
    else if (Board[BOARD_SIZE-Pos.x][Pos.y-'A'] == BLACK_CIR ||
             Board[BOARD_SIZE-Pos.x][Pos.y-'A'] == BLACK_TRI ||
             Board[BOARD_SIZE-Pos.x][Pos.y-'A'] == WHITE_CIR ||
             Board[BOARD_SIZE-Pos.x][Pos.y-'A'] == WHITE_TRI) {
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
    printf("坐标: ");
}

int StartPvP()
{
    InitBoardArray();
    DisplayBoard();

    while (1) 
    {   
        GetValidPosition(ROUND_BLACK); 
        Board[BOARD_SIZE-Pos.x][Pos.y-'A'] = BLACK_TRI;
        DisplayBoard(); 
        Board[BOARD_SIZE-Pos.x][Pos.y-'A'] = BLACK_CIR;

        GetValidPosition(ROUND_WHITE);
        Board[BOARD_SIZE-Pos.x][Pos.y-'A'] = WHITE_TRI;
        DisplayBoard();
        Board[BOARD_SIZE-Pos.x][Pos.y-'A'] = WHITE_CIR;
    }   

    return 0;
}
