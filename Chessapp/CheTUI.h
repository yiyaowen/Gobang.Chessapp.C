#ifndef INCLUDE_CHE_TUI_H
#define INCLUDE_CHE_TUI_H

#include "CheDef.h"

//////////////
// Home TUI //
//////////////

/**
 * Display total Homepage
 *
 * @param
 * @return
 */
void DisplayHomePage();

/**
 * Print Homepage options
 *
 * @param
 * @return
 */
void PrintHomeOptions();

/**
 * Loop until get a valid input for homepage option
 *
 * @param
 * @return
 */
void GetValidHomeOption();

/**
 * Check if iOption is a valid homepage option
 *
 * @param iOption (The option to be checked)
 * @return (If iOption is valid return 1, otherwise return 0)
 */
int IsHomeOptionValid(int iOption);

/**
 * Display page [CurrentOptionNum]
 *
 * @param
 * @return
 */
void SwitchToSelectedHomeOption();

///////////////
// Board TUI //
///////////////

/**
 * Display Game Info Frame and Chessboard
 *
 * @param
 * @return
 */
void DisplayBoard();

/* iRound */
#define ROUND_BLACK         1
#define ROUND_WHITE         2

/**
 * Display input hint for the specific side
 *
 * @param iRound (ROUND_WHITE or ROUND_BLACK)
 * @return
 */
void PrintHint(int iRound);

/**
 * Loop until get a valid input for Chessboard position
 *
 * @param iRound (ROUND_WHITE or ROUND_BLACK)
 * @param pos (The position that has been selected)
 * @return (The valid position from user input)
 */
POSITION GetValidPosition(int iRound, POSITION pos);

/**
 * Check if the option is a special control option
 *
 * @param key (The option to be checked)
 * @return (If it is a special control option return 1, otherwise return 0)
 */
int IsSpecialControlOption(char key);

/**
 * Handle special control options when playing
 *
 * @param key (The special control option)
 * @param inPos (The position that will be modified)
 * @return
 */
void HandleControlOption(char key, POSITION * inPos);

/**
 * Check if pos is a valid Chessboard position
 *
 * @param pos (The position to be checked)
 * @return iErrorType (If pos is valid return POS_VALID, otherwise return specific error type)
 */
int IsPositionValid(POSITION pos);

/* iErrorType */
#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

/**
 * Display error hint of the specific error type
 *
 * @param iErrorType (The type of input error)
 * @return
 */
void PrintErrorHint(int iErrorType);

/**
 * Start handle PvP game. Loop until the game is over
 *
 * @param game_prefab_config (Prefab configuration of game)
 * @return iOptionResult (The handle result of subroutine)
 */
int StartPvP(GAME_PREFAB_CONFIG game_prefab_config);

/**
 * Start handle PvC game. Loop until the game is over
 *
 * @param game_prefab_config (Prefab configuration of game)
 * @return iOptionResult (The handle result of subroutine)
 */
int StartPvC(GAME_PREFAB_CONFIG game_prefab_config);

/**
 * Display total "Preferences & Settings" pgae.
 *
 * @param iOption (The option selected now, used by [PrintPreAndSetOptions])
 * @return
 */
void DisplayPreAndSetPage(int iOption);

/**
 * Print options of "Preferences & Settings" page.
 *
 * @param iOption (The option selected now, and it will be highlighted)
 * @return
 */
void PrintPreAndSetOptions(int iOption);

/**
 * Print single option of "Preferences & Settings" page.
 *
 * @param iOption (The option selected now)
 * @param iOptionNum (The number code of option)
 * @param szOptionText (The text of option)
 * @return
 */
void PrintPreAndSetOption(int iOption, int iOptionNum, const char *szOptionText);

/**
 * Loop until get a valid option for "Preferences & Settings" page.
 *
 * @param
 * @return iOption(The valid option selected)
 */
int GetValidPreAndSetOption();

/**
 * Check if iOption is a valid option for "Preferences & Settings" page.
 *
 * @param iOption (The option to be checked)
 * @return (If iOption is valid return 1, otherwise return 0)
 */
int IsPreAndSetOptionValid(int iOption);

/**
 * Display page [iOption]
 *
 * @param iOption (The page to be displayed)
 * @return
 */
void SwitchToSelectedPreAndSetOption(int iOption);

/**
 * Start handle "Preferences & Settings" page.
 *
 * @param
 * @return iOptionResult (The handle result of subroutine)
 */
int StartPreAndSet();

/**
 * Display total "About Chessplayer" page.
 *
 * @param
 * @return
 */
void DisplayAboutChePage();

/**
 * Print content of "About Chessplayer" page.
 *
 * @param
 * @return
 */
void PrintAboutCheContent();

/**
 * Start handle "About Chessplayer" page.
 *
 * @param
 * @return iOptionResult (The handle result of subroutine)
 */
int StartAboutChe();

/**
 * Display total "About Project" page with specific content.
 *
 * @param iOption (Different options correspond to different contents)
 * @return
 */
void DisplayAboutProPage(int iOption);

/**
 * Print content of "About Project" page.
 *
 * @param
 * @return
 */
void PrintAboutProContent();
void PrintAboutProEasterEgg1Content();
void PrintAboutProEasterEgg2Content();

/**
 * Get valid option for "About Project" page.
 *
 * @param
 * @return iOption (The valid option for "About Project" page)
 */
int GetValidAboutProOption();

/**
 * Start handle "About Project" page.
 *
 * @param
 * @return iOptionResult (The handle result of subroutine)
 */
int StartAboutPro();

/* iOptionResult */
#define OPT_ABORT  -1
#define OPT_QUIT    0

#endif /* INCLUDE_CHE_TUI_H */
