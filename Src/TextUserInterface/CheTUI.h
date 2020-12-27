#ifndef CHE_TUI_H
#define CHE_TUI_H

#include "CheDef.h"

#define PAGE_TEMPLATE(PAGE_NAME) \
void Display ## PAGE_NAME ## Page(PageInfo info); \
Route* Handle ## PAGE_NAME ## Page(Route* route, PageInfo info);

PAGE_TEMPLATE(Home)
PAGE_TEMPLATE(Game)
PAGE_TEMPLATE(PreAndSet)
PAGE_TEMPLATE(AboutChe)
PAGE_TEMPLATE(AboutPro)

Route* StartPvP(Route* route, GAME_PREFAB_CONFIG game_prefab_config);
Route* StartPvC(Route* route, GAME_PREFAB_CONFIG game_prefab_config);

void PrintHint(int iRound);

/**
 * Get a valid chessboard position from user input.
 *
 * @param iRound (ROUND_BLACK or ROUND_WHITE)
 * @param pos (Last position selected)
 * @return pos_
 */
POSITION GetValidPositionFromUser(int iRound, POSITION pos);

int IsSpecialControlOption(char key);

void HandleControlOption(char key, POSITION *pos);

int IsPositionValid(POSITION pos);

#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

void PrintErrorHint(int iErrorType);

#endif // CHE_TUI_H
