#ifndef INCLUDE_CHE_GLOBAL_H
#define INCLUDE_CHE_GLOBAL_H

#include "CheDef.h"
#include "CheTUI.h"

/**
 * Initialize all global variables
 *
 * @param
 * @return
 */
void InitGlobalVariables();

////////////////
// Global TUI //
////////////////

extern PageStack PS;

/**
 * Initialize page stack.
 *
 * @param
 * @return
 */
void InitPageStack();

//////////////
// Home TUI //
//////////////

extern HOME_OPTIONS HomeOptions;
extern int CurrentOptionNum;

/**
 * Initialize home options.
 *
 * @param
 * @return
 */
void InitHomeOptionsArray();

///////////////
// Board TUI //
///////////////

extern DEFAULT_FLAT_BOARD Board;

/**
 * Initialize Chessboard
 *
 * @param
 * @return
 */
void InitBoardArray();

///////////////
// Game data //
///////////////

extern GAME_RECORD_BOARD RecordBoard;

/**
 * Initialize Record Chessboard
 * 
 * @param
 * @return
 */
void InitRecordBoardArray();

#endif /* INCLUDE_CHE_GLOBAL_H */
