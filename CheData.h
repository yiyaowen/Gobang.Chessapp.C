#ifndef _INCLUDE_CHE_DATA
#define _INCLUDE_CHE_DATA

#include "CheDef.h"

/* [Check if game is over and decide the winner]
 * @param iRecordType (RECORD_BLACK or RECORD_WHITE)
 * @return iGameResult (Go on, win or tied)
 */
int GetGameResult(int iRecordType);

/* iGameResult */
#define GR_GOON     0
#define GR_WIN      1
#define GR_TIED     4
/* DEPRECATED !!! */
/*
#define GR_BLACK_WIN    2
#define GR_WHITE_WIN    3
*/

/* SIDE_WIN_INFO */
#define SWI_WIN     0
#define SWI_GOON    1
typedef struct {
    int win;
    INDEXER aIdx[5];
    POSITION aPos[5];
} SIDE_WIN_INFO;

/* [Check if the specific side is win]
 * @param iRecordType (RECORD_BLACK or RECORD_WHITE)
 * @return side_win_info (If win win=SWI_WIN, aIdx and aPos will be set, otherwise win=SWI_GOON, aIdx and aPos will keep empty)
 */
SIDE_WIN_INFO IsSideWin(int iRecordType);

/* [Check if the specific side has a subtype-win]
 * @param iRecordType (RECORD_BLACK or RECORD_WHITE)
 * @return side_win_info (Redirect to IsSideWin)
 */
SIDE_WIN_INFO IsSideWinRow(int iRecordType);
SIDE_WIN_INFO IsSideWinCol(int iRecordType);
SIDE_WIN_INFO IsSideWinBDiag(int iRecordType);
SIDE_WIN_INFO IsSideWinFDiag(int iRecordType);

/* [Convert POSITION to INDEXER]
 * @param ptPos (Convert source position)
 * @param ptIdx (Convert target indexer)
 * @return
 */
void PosToIdx(const POSITION * ptPos, INDEXER * ptIdx);

/* [Convert INDEXER to POSITION]
 * @param ptIdx (Convert source indexer)
 * @param ptPos (Convert target position)
 * @return
 */
void IdxToPos(const INDEXER * ptIdx, POSITION * ptPos);

#endif /* _INCLUDE_CHE_DATA */
