#ifndef INCLUDE_CHE_DATA
#define INCLUDE_CHE_DATA

#include "CheDef.h"

//////////////////////////////////
// Data analysis and conversion //
//////////////////////////////////

/**
 * Check if game is over and decide the winner
 *
 * @param iRecordType (RECORD_BLACK or RECORD_WHITE)
 * @return iGameResult (Go on, win or tied)
 */
int GetGameResult(int iRecordType);

/* iGameResult */
#define GR_GOON     0
#define GR_WIN      1
#define GR_TIED     4

/* SIDE_WIN_INFO */
#define SWI_WIN     0
#define SWI_GOON    1
typedef struct {
    int win;
    INDEXER aIdx[5];
    POSITION aPos[5];
} SIDE_WIN_INFO;

/**
 * Check if the specific side is win
 *
 * @param iRecordType (RECORD_BLACK or RECORD_WHITE)
 * @return side_win_info
 * (
 * If win win=SWI_WIN, aIdx and aPos will be set.
 * Otherwise win=SWI_GOON, aIdx and aPos will keep empty.
 * )
 */
SIDE_WIN_INFO IsSideWin(int iRecordType);

/**
 * Check if the specific side has a subtype-win
 *
 * @param iRecordType (RECORD_BLACK or RECORD_WHITE)
 * @return side_win_info (Redirect to [IsSideWin])
 */
SIDE_WIN_INFO IsSideWinRow(int iRecordType);
SIDE_WIN_INFO IsSideWinCol(int iRecordType);
SIDE_WIN_INFO IsSideWinBDiag(int iRecordType);
SIDE_WIN_INFO IsSideWinFDiag(int iRecordType);

/**
 * Convert POSITION to INDEXER
 *
 * @param ptPos (Source position)
 * @param ptIdx (Target indexer)
 * @return
 */
void PosToIdx(const POSITION * ptPos, INDEXER * ptIdx);

/**
 * Convert POSITION.x to INDEXER.i
 *
 * @param x (Source POSITION.x)
 * @return i (Target INDEXER.i)
 */
int Pos_xToIdx_i(int x);

/**
 * Convert POSITION.y to INDEXER.j
 *
 * @param y (Source POSITION.y)
 * @return j (Target INDEXER.j)
 */
int Pos_yToIdx_j(char y);

/**
 * Convert INDEXER to POSITION
 *
 * @param ptIdx (Source indexer)
 * @param ptPos (Target position)
 * @return
 */
void IdxToPos(const INDEXER * ptIdx, POSITION * ptPos);

/**
 * Convert INDEXER.i to POSITION.x
 * 
 * @param i (Source INDEXER.i)
 * @return x (Target POSITION.x)
 */
int Idx_iToPos_x(int i);

/**
 * Convert INDEXER.j to POSITION.y
 * 
 * @param j (Source INDEXER.j)
 * @return y (Target POSITION.y)
 */
char Idx_jToPos_y(int j);

////////////////////////////
// Data import and export //
////////////////////////////

/**
 * Export specific board array data
 *
 * @param board (The board to be exported)
 * @param path (Target file path)
 * @return (If success return 1, otherwise return 0)
 */
int ExportBoardToFile(int board[][BOARD_SIZE], const char * path);

/////////////////
// Data update //
/////////////////

/**
 * Update global board arrays
 *
 * Board-list:
 *      [Board]
 *      [RecordBoard]
 *
 * @param iTotalRound (Count of total game round)
 * @param iRound (ROUND_BLACK or ROUND_WHITE)
 * @param lastPos (Last board position selected)
 * @param pos (Board position selected)
 * @return
 */
void UpdateGlobalBoardArrays(int iTotalRound, int iRound, POSITION lastPos, POSITION pos);

#endif /* INCLUDE_CHE_DATA */
