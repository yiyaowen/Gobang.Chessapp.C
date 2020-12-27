#include "CheDef.h"
#include "CheTUI.h"
#include "CheGlobal.h"

int CurrentOptionNum;

void InitGlobalVariables()
{
    /* Global TUI */
    InitPageStack();

    /* Home TUI */
    InitHomeOptionsArray();
    CurrentOptionNum = OPTION_PvP_NUM;

    /* Board TUI */
    InitBoardArray();
    
    /* Game data */
    InitRecordBoardArray();
}

PageStack PS;

void InitPageStack()
{
    PS.count = 0;
}

HOME_OPTIONS HomeOptions;

void InitHomeOptionsArray()
{
    HomeOptions[0] = HOME_OPTION_PvP;
    HomeOptions[1] = HOME_OPTION_PvC;
    HomeOptions[2] = HOME_OPTION_PreAndSet;
    HomeOptions[3] = HOME_OPTION_AboutChe;
    HomeOptions[4] = HOME_OPTION_AboutPro;
    HomeOptions[5] = HOME_OPTION_Exit;
}

DEFAULT_FLAT_BOARD Board;

void InitBoardArray()
{
    int i, j;
    
    Board[0][0] = GRID_LEFT_TOP;
    Board[0][BOARD_SIZE-1] = GRID_RIGHT_TOP;
    Board[BOARD_SIZE-1][BOARD_SIZE-1] = GRID_RIGHT_BOTTOM;
    Board[BOARD_SIZE-1][0] = GRID_LEFT_BOTTOM;
    
    for (j = 1; j <= BOARD_SIZE - 2; ++j) {
        Board[j][0] = GRID_LEFT;
    }
    
    for (i = 1; i <= BOARD_SIZE - 2; ++i) {
        Board[0][i] = GRID_TOP;
    }
    
    for (j = 1; j <= BOARD_SIZE - 2; ++j) {
        Board[j][BOARD_SIZE - 1] = GRID_RIGHT;
    }
    
    for (i = 1; i <= BOARD_SIZE - 2; ++i) {
        Board[BOARD_SIZE - 1][i] = GRID_BOTTOM;
    }
    
    for (j = 1; j <= BOARD_SIZE - 2; ++j) {
        for (i = 1; i <= BOARD_SIZE - 2; ++i) {
            Board[j][i] = GRID_MIDDLE;
        }
    }
}

GAME_RECORD_BOARD RecordBoard;

void InitRecordBoardArray()
{
    int i, j;
    
    for (i = 0; i < BOARD_SIZE; ++i) {
        for (j = 0; j < BOARD_SIZE; ++j) {
            RecordBoard[i][j] = 0;
        }
    }
}
