#ifndef _INCLUDE_CHE_TUI_H
#define _INCLUDE_CHE_TUI_H

#include "CheDef.h"

//////////////
// Home TUI //
//////////////

/* [Display Homepage options]
 * @param
 * @return
 */
void DisplayHomeOptions();

/* [Display Total Homepage]
 * @param
 * @return
 */
void DisplayHome();

/* [Loop until get a valid input for homepage option]
 * @param
 * @return
 */
void GetValidHomeOption();

/* [Check if iOption is a valid homepage option]
 * @param iOption (The option to be checked)
 * @return (If iOption is valid return 1, otherwise return 0)
 */
int IsOptionValid(int iOption);

/* [Display page of global variable CurrentOptionNum]
 * @param
 * @return
 */
void SwitchToSelectedOption();

///////////////
// Board TUI //
///////////////

/* [Display Game Info Frame and Chessboard]
 * @param
 * @return
 */
void DisplayBoard();

/* [Display input hint of the specific side]
 * @param iRound (ROUND_WHITE or ROUND_BLACK)
 * @return
 */
void DisplayHint(int iRound);

/* [Loop until get a valid input for Chessboard position]
 * @param iRound (ROUND_WHITE or ROUND_BLACK)
 * @param pos (The position that has been selected)
 * @return (The valid position from user input)
 */
POSITION GetValidPosition(int iRound, POSITION pos);

/* [Check if the option is a special control option]
 * @param key (The option to be checked)
 * @return (If it is a special control option return 1, otherwise return 0)
 */
int IsSpecialControlOption(char key);

/* [Handle special control options when playing]
 * @param key (The special control option)
 * @param inPos (The origin position before handling)
 * @return outPos (The modified position after handling)
 */
POSITION HandleControlOption(char key, POSITION inPos);

/* iRound */
#define ROUND_BLACK         1
#define ROUND_WHITE         2

/* [Check if pos is a valid Chessboard position]
 * @param pos (The position to be checked)
 * @return iErrorType (If pos is valid return POS_VALID, otherwise return specific error type)
 */
int IsPositionValid(POSITION pos);

/* [Display error hint of the specific error type]
 * @param iErrorType (The type of input error)
 * @return
 */
void DisplayErrorHint(int iErrorType);

/* iErrorType */
#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

/* [Start handle PvP game. Loop until the game is over]
 * @param
 * @return iOptionResult (The handle result of subroutine)
 */
int StartPvP();

/* iOptionResult */
#define OPT_ABORT  -1
#define OPT_QUIT    0

#endif /* _INCLUDE_CHE_TUI_H */
