#include "Cor.h"

COR_INDEXER GetCoreAnalysisResultI(COR_GAME_RECORD_BOARD board, ANALYSIS_PREFAB_CONFIG analysis_prefab_config)
{
    COR_INDEXER cor_indexer;

    switch (analysis_prefab_config.level)
    {
    case APC_LEVEL_DRUNK:
        srand(time(0));
        cor_indexer.i = rand() % COR_BOARD_SIZE;
        cor_indexer.j = rand() % COR_BOARD_SIZE;
        while (board[cor_indexer.i][cor_indexer.j] * analysis_prefab_config.side != 0) {
            cor_indexer.i = rand() % COR_BOARD_SIZE;
            cor_indexer.j = rand() % COR_BOARD_SIZE;
        }
        return cor_indexer;

    case APC_LEVEL_LOW:
        // TODO
        return cor_indexer;

    case APC_LEVEL_MIDDLE:
        // TODO
        return cor_indexer;

    case APC_LEVEL_HIGH:
        // TODO
        return cor_indexer;

    case APC_LEVEL_INVINCIBLE:
        // TODO
        return cor_indexer;

    case APC_LEVEL_RANDOM:
        // TODO
        return cor_indexer;

    default:
        // TODO
        return cor_indexer;
    }
}

COR_POSITION GetCoreAnalysisResultP(COR_GAME_RECORD_BOARD board, ANALYSIS_PREFAB_CONFIG analysis_prefab_config)
{
    COR_POSITION cor_position; 
    COR_INDEXER cor_indexer = GetCoreAnalysisResultI(board, analysis_prefab_config);
    CorIdxToCorPos(&cor_indexer, &cor_position);
    return cor_position;
}

void CorPosToCorIdx(const COR_POSITION * ptCorPos, COR_INDEXER * ptCorIdx)
{
    ptCorIdx->i = COR_BOARD_SIZE - ptCorPos->x;
    ptCorIdx->j = ptCorPos->y - 'A';
}

void CorIdxToCorPos(const COR_INDEXER * ptCorIdx, COR_POSITION * ptCorPos)
{
    ptCorPos->x = COR_BOARD_SIZE - ptCorIdx->i;
    ptCorPos->y = ptCorIdx->j + 'A';
}
