#include "CheDef.h"
#include "CheTUI.h"
#include "CheGlobal.h"

extern HOME_OPTIONS HomeOptions;
extern int CurrentOptionNum;

extern DEFAULT_FLAT_BOARD Board;

void InitHomeOptionsArray()
{
    HomeOptions[0] = HOME_OPTION_PvP;
    HomeOptions[1] = HOME_OPTION_PvC;
    HomeOptions[2] = HOME_OPTION_PreAndSet;
    HomeOptions[3] = HOME_OPTION_AboutChe;
    HomeOptions[4] = HOME_OPTION_AboutPro;
    HomeOptions[5] = HOME_OPTION_Exit;
}

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

void InitGlobalVariables()
{
    /* Home TUI */
    InitHomeOptionsArray();
    CurrentOptionNum = OPTION_PvP_NUM;

    /* Board TUI */
    InitBoardArray();
}
