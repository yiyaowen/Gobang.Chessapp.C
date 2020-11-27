#include "CheDef.h"
#include "CheData.h"
#include "CheGlobal.h"
#include "CheTUI.h"

extern DEFAULT_FLAT_BOARD Board;
extern GAME_RECORD_BOARD RecordBoard;

//////////////////////////////////
// Data analysis and conversion //
//////////////////////////////////

int GetGameResult(int iRecordType)
{
    SIDE_WIN_INFO side_win_info;

    side_win_info = IsSideWin(iRecordType);
    if (side_win_info.win == SWI_WIN) {
        return GR_WIN;
    }
    // TODO
    return GR_GOON;
}

SIDE_WIN_INFO IsSideWin(int iRecordType)
{
    SIDE_WIN_INFO side_win_info;

    // Check rows
    side_win_info = IsSideWinRow(iRecordType);
    if (side_win_info.win == SWI_WIN) {
        return side_win_info;
    }
    // Check cols
    side_win_info = IsSideWinCol(iRecordType);
    if (side_win_info.win == SWI_WIN) {
        return side_win_info;
    }
    // Check B-Diag
    side_win_info = IsSideWinBDiag(iRecordType);
    if (side_win_info.win == SWI_WIN) {
        return side_win_info;
    }
    // Check F-Diag
    side_win_info = IsSideWinFDiag(iRecordType);
    if (side_win_info.win == SWI_WIN) {
        return side_win_info;
    }

    return side_win_info;
}

SIDE_WIN_INFO IsSideWinRow(int iRecordType)
{
    int i, j, k;
    SIDE_WIN_INFO side_win_info;
    // Check rows
    for (i = 0; i < BOARD_SIZE; ++i) {
        for (j = 0; j <= BOARD_SIZE-5; j+=(k+1)) {
            /* Retrieve continuous 5 position */
            for (k = 0; k < 5; ++k) {
                if ((RecordBoard[i][j+k] * iRecordType) > 0) {
                    /* Winning */
                    if (k == 4) {
                        side_win_info.win = SWI_WIN;
                        for (int index = 0; index < 5; ++index) {
                            POSITION tmpPos;
                            INDEXER tmpIdx = { i, j+index };
                            IdxToPos(&tmpIdx, &tmpPos);
                            side_win_info.aIdx[index] = tmpIdx;
                            side_win_info.aPos[index] = tmpPos;
                        }
                        return side_win_info;
                    }
                    /* Winning */
                }
                else {
                    break;
                }
            }
            /* Retrieve continuous 5 position */
        }
    }
    side_win_info.win = SWI_GOON;
    return side_win_info;
}

SIDE_WIN_INFO IsSideWinCol(int iRecordType)
{
    int i, j, k;
    SIDE_WIN_INFO side_win_info;
    // Check cols
    for (j = 0; j < BOARD_SIZE; ++j) {
        for (i = 0; i <= BOARD_SIZE-5; ++i) {
            /* Retrieve continuous 5 position */
            for (k = 0; k < 5; ++k) {
                if ((RecordBoard[i+k][j] * iRecordType) > 0) {
                    /* Winning */
                    if (k == 4) {
                        side_win_info.win =SWI_WIN;
                        for (int index = 0; index < 5; ++index) {
                            POSITION tmpPos;
                            INDEXER tmpIdx = { i+index, j };
                            IdxToPos(&tmpIdx, &tmpPos);
                            side_win_info.aIdx[index] = tmpIdx;
                            side_win_info.aPos[index] = tmpPos;
                        }
                        return side_win_info;
                    }
                    /* Winning */
                }
                else {
                    break;
                }
            }
            /* Retrieve continuous 5 position */
        }
    }
    side_win_info.win = SWI_GOON;
    return side_win_info;
}

SIDE_WIN_INFO IsSideWinBDiag(int iRecordType)
{
    int i, j, k;
    SIDE_WIN_INFO side_win_info;
    // Check B-Diag
    for (i = 0; i <= BOARD_SIZE-5; ++i) {
        for (j = 4; j < BOARD_SIZE; ++j) {
            /* Retrieve continuous 5 position */
            for (k = 0; k < 5; ++k) {
                if ((RecordBoard[i+k][j-k] * iRecordType) > 0) {
                    /* Winning */
                    if (k == 4) {
                        side_win_info.win =SWI_WIN;
                        for (int index = 0; index < 5; ++index) {
                            POSITION tmpPos;
                            INDEXER tmpIdx = { i+index, j-index };
                            IdxToPos(&tmpIdx, &tmpPos);
                            side_win_info.aIdx[index] = tmpIdx;
                            side_win_info.aPos[index] = tmpPos;
                        }
                        return side_win_info;
                    }
                    /* Winning */
                }
                else {
                    break;
                }
            }
            /* Retrieve continuous 5 position */
        }
    }
    side_win_info.win = SWI_GOON;
    return side_win_info;
}

SIDE_WIN_INFO IsSideWinFDiag(int iRecordType)
{
    int i, j, k;
    SIDE_WIN_INFO side_win_info;
    // Check F-Diag
    for (i = 0; i <= BOARD_SIZE-5; ++i) {
        for (j = 0; j <= BOARD_SIZE-5; ++j) {
            /* Retrieve continuous 5 position */
            for (k = 0; k < 5; ++k) {
                if ((RecordBoard[i+k][j+k] * iRecordType) > 0) {
                    /* Winning */
                    if (k == 4) {
                        side_win_info.win =SWI_WIN;
                        for (int index = 0; index < 5; ++index) {
                            POSITION tmpPos;
                            INDEXER tmpIdx = { i+index, j+index };
                            IdxToPos(&tmpIdx, &tmpPos);
                            side_win_info.aIdx[index] = tmpIdx;
                            side_win_info.aPos[index] = tmpPos;
                        }
                        return side_win_info;
                    }
                    /* Winning */
                }
                else {
                    break;
                }
            }
            /* Retrieve continuous 5 position */
        }
    }
    side_win_info.win = SWI_GOON;
    return side_win_info;
}

void PosToIdx(const POSITION * ptPos, INDEXER * ptIdx)
{
    ptIdx->i = BOARD_SIZE - ptPos->x;
    ptIdx->j = ptPos->y - 'A';
}

int Pos_xToIdx_i(int x)
{
    return BOARD_SIZE - x;
}

int Pos_yToIdx_j(char y)
{
    return y - 'A';
}

void IdxToPos(const INDEXER * ptIdx, POSITION * ptPos)
{
    ptPos->x = BOARD_SIZE - ptIdx->i;
    ptPos->y = ptIdx->j + 'A';
}

int Idx_iToPos_x(int i)
{
    return BOARD_SIZE - i;
}

char Idx_jToPos_y(int j)
{
    return j + 'A';
}

////////////////////////////
// Data import and export //
////////////////////////////

int ExportBoardToFile(int board[][BOARD_SIZE], const char * path)
{
    FILE * fp = fopen(path, "w");
    if (fp == NULL) {
        return 0;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE-1; ++j) {
            fprintf(fp, "%d ", board[i][j]);
        }
        fprintf(fp, "%d\n", board[i][BOARD_SIZE-1]);
    }

    fclose(fp);
    return 1;
}

/////////////////
// Data update //
/////////////////

void UpdateGlobalBoardArrays(int iTotalRound, int iRound, POSITION lastPos, POSITION pos)
{
    INDEXER lastIdx, idx;
    PosToIdx(&lastPos, &lastIdx);
    PosToIdx(&pos, &idx);

    if (iRound == ROUND_BLACK) {
        Board[idx.i][idx.j] = BLACK_TRI;
        /* Skip 1st round */
        if (iTotalRound-1) Board[lastIdx.i][lastIdx.j] = WHITE_CIR;
        RecordBoard[idx.i][idx.j] = RECORD_BLACK * iTotalRound;
    }
    else {
        Board[idx.i][idx.j] = WHITE_TRI;
        Board[lastIdx.i][lastIdx.j] = BLACK_CIR;
        RecordBoard[idx.i][idx.j] = RECORD_WHITE * iTotalRound;
    }
}
