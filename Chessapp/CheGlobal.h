#ifndef INCLUDE_CHE_GLOBAL_H
#define INCLUDE_CHE_GLOBAL_H

#include "CheDef.h"

//////////////
// Home TUI //
//////////////

HOME_OPTIONS HomeOptions;
int CurrentOptionNum;

///////////////
// Board TUI //
///////////////

DEFAULT_FLAT_BOARD Board;

/**
 * Initialize home options
 *
 * @param
 * @return
 */
void InitHomeOptionsArray();

/**
 * Initialize Chessboard
 *
 * @param
 * @return
 */
void InitBoardArray();

/**
 * Initialize all gobal variables
 *
 * @param
 * @return
 */
void InitGlobalVariables();

///////////////
// Game data //
///////////////

GAME_RECORD_BOARD RecordBoard;

/**
 * Initialize Record Chessboard
 * 
 * @param
 * @return
 */
void InitRecordBoardArray();

#endif /* INCLUDE_CHE_GLOBAL_H */
