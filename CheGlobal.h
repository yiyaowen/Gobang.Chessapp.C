#ifndef _INCLUDE_CHE_GLOBAL_H
#define _INCLUDE_CHE_GLOBAL_H

#include "CheDef.h"
#include "CheTUI.h"

//////////////
// Home TUI //
//////////////

HOME_OPTIONS HomeOptions;
int CurrentOptionNum;

///////////////
// Board TUI //
///////////////

DEFAULT_FLAT_BOARD Board;

/* [Initialize home options]
 * @param
 * @return
 */
void InitHomeOptionsArray();

/* [Initialize Chessboard]
 * @param
 * @return
 */
void InitBoardArray();

/* [Initialize all gobal variables]
 * @param
 * @return
 */
void InitGlobalVariables();

#endif /* _INCLUDE_CHE_GLOBAL_H */
