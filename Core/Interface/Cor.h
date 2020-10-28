#ifndef COR_H
#define COR_H

#include "CorDef.h"

// Default return result as indexer
#define GetCoreResult GetCoreResultI

/**
 * Get core's analysis result as indexer
 *
 * @param board (The board to be analysed)
 * @param analysis_prefb_config (Prefab configuration of core analysis)
 * @return cor_indexer (Analysis result as indexer)
 */
COR_INDEXER GetCoreResultI(COR_GAME_RECORD_BOARD board, ANALYSIS_PREFAB_CONFIG analysis_prefb_config);

/**
 * Get core's analysis result as position. 
 * This function is simply redirected to GetCoreResultI.
 * After get result as indexer, it is converted as position and then return.
 *
 * @param board (The board to be analysed)
 * @param analysis_prefb_config (Prefab configuration of core analysis)
 * @return cor_position (Analysis result as position)
 */
COR_POSITION GetCoreResultP(COR_GAME_RECORD_BOARD board, ANALYSIS_PREFAB_CONFIG analysis_prefb_config);

/**
 * Convert COR_POSITION to COR_INDEXER
 *
 * @param ptCorPos (Source core position)
 * @param ptCorIdx (Target core indexer)
 * @return
 */
void CorPosToCorIdx(const COR_POSITION * ptCorPos, COR_INDEXER * ptCorIdx);

/**
 * Convert COR_INDEXE to COR_POSITION
 *
 * @param ptCorIdx (Source core indexer)
 * @param ptCorPos (Target core position)
 * @return
 */
void CorIdxToCorPos(const COR_INDEXE * ptCorIdx, COR_POSITION * ptCorPos);
