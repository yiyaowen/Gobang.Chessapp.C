#include "CheDef.h"

#ifndef _INCLUDE_CHE_TUI_H
#define _INCLUDE_CHE_TUI_H

//////////////
// Home TUI //
//////////////

void DisplayHomeOptions();

void DisplayHome();

void GetValidHomeOption();

int IsOptionValid(int iOption);

void SwitchToSelectedOption();

///////////////
// Board TUI //
///////////////

void DisplayBoard();

void DisplayHint(int iRound);

POSITION GetValidPosition(int iRound, POSITION pos);
/* iRound */
#define ROUND_BLACK         1
#define ROUND_WHITE         2

int IsPositionValid(POSITION pos);
/* iErrorType */
#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

void DisplayErrorHint(int iErrorType);

int StartPvP();
/* iOptionResult */
#define OPT_ABORT  -1
#define OPT_QUIT    0

#endif /* _INCLUDE_CHE_TUI_H */
