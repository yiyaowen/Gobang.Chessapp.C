#ifndef CORE_H
#define CORE_H

#include "CoreDefinitions.h"

/**
 * Initialize gobang core.
 * If you invoke any gobang core function before initializing, the result will be undefined.
 */
 void initializeGobangCore();

 /**
  * Release gobang core.
  * If you invoke any gobang core function after releasing, the result will be undefined.
  */
  void releaseGobangCore();

/**
 * Create a new gobang game with the specific tag.
 *
 * @param tag The tag of new gobang game.
 *
 * @param favors The side in the new gobang game you want to analyse, which should not be changed
 *               during a gobang game's life cycle. Otherwise the analysis result of gobang game
 *               will be undefined and the error will be irreversible. If the favors is changed by
 *               accident, it is recommended to create another new gobang game with the same favors.
 *				 If the favors is [CORE_SIDE_EMPTY], the new gobang game created will not do any
 *				 analysis, which means that [getCorePointFromCoreAlgorithm] does not work. However,
 *				 you can still use [getWinnerSideInCoreGameWithTag] to judge whether the game is over.
 */
void createNewCoreGameWithTag(CoreGameTag tag, CoreSide favors);

/**
 * Add new move piece to the specific gobang game.
 *
 * @param side This should be one of the following values: [CORE_SIDE_BLACK for black piece],
 *             [CORE_SIDE_WHITE for white piece], [CORE_SIDE_EMPTY for null]. If the side is
 *             [CORE_SIDE_EMPTY], the function will do nothing and return directly.
 *
 * @param point The point of new move piece in the gobang game board. [point.i] represents the
 *              row index, and [point.j] represents the column index of the point. Both of the
 *              indexes should be a valid integer, i.e. in the range of [0, CORE_BOARD_SIZE - 1],
 *              otherwise the function will do nothing and return directly. One exception is that
 *              if the point is within the game board but the position has been occupied, the new
 *              point will not be added to the gobang game. In this case nothing will change.
 *
 * @param tag The tag of the specific gobang game. If the gobang game with such tag already exists,
 *            the new move piece will be added to it directly. Otherwise a new gobang game with the
 *            specific tag will be created, and then the new move piece will be added. One exception
 *            is that if the total count of gobang game already reaches the maximum count, one of the
 *            gobang games created before will be removed directly to make space for the new gobang
 *            game. You can remove the useless gobang game manually to prevent this from happening.
 */
 void addNewMovePieceToCoreGameWithTag(CoreSide side, CorePoint point, CoreGameTag tag);

 void removeCoreGameWithTag(CoreGameTag tag);

/**
 * Get the analysis result from core algorithm.
 *
 * @param config The prefab configuration of analysis. This struct includes two configurable fields:
 *               [CoreSide side], which should be one of the following values: [CORE_SIDE_BLACK for
 *               black side], [CORE_SIDE_WHITE for white side], [CORE_SIDE_EMPTY for null].
 *               [CoreLevel level], which should be one of the following values: [CORE_LEVEL_DRUNK],
 *               [CORE_LEVEL_LOW], [CORE_LEVEL_MIDDLE], [CORE_LEVEL_HIGH] and [CORE_LEVEL_RANDOM].
 *               If [config.side] is [CORE_SIDE_EMPTY] or an invalid value, or [config.level] is an
 *               invalid value, the function will return (-1, -1) directly without analysis.
 *
 * @param tag Use this field to specify the gobang game to analyse. The function will return the best
 *            move point for the specific prefab configuration. If the gobang game with specific tag
 *            does not exist or the board is already full, the function will return (-1, -1) instead.
 *
 * @return The best move point for the specific prefab configuration.
 */
 CorePoint  getCorePointFromCoreAlgorithm(const CorePrefabConfig* config, CoreGameTag tag);

 /**
 * Get winner side in the specific gobang game if it is over.
 * 
 * @param tag The tag of the specific gobang game.
 * 
 * @return If the game is over, the function will return the winner side, i.e. [CORE_SIDE_BLACK] or
 *		   [CORE_SIDE_WHITE]. Otherwise it will return [CORE_SIDE_EMPTY] directly.
 */
 CoreSide getWinnerSideInCoreGameWithTag(CoreGameTag tag);

#endif // CORE_H
