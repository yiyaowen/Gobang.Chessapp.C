#include <stdio.h>

#include "Cor.h"

int main()
{
    int board[COR_BOARD_SIZE][COR_BOARD_SIZE] = {
    -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, 10,  0,  0, 14,  0,  0,  0,  0,  0,  0,
    0,  2,  0,  0,  0,  0,  8,  0,  0,-15,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, -9,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0, -3,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0, -7,  0,  0,-13,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,-17,  0,  4,  0,  0,  0,  0,  0, 12,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0, -5,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,-11,  0,  0,  0, 20,  0,  0,  0,
    0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-19,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };

    int side;
    for (int i = 0; i < 100; ++i) {
        side = (i%2 == 0) ? APC_SIDE_BLACK : APC_SIDE_WHITE;
        ANALYSIS_PREFAB_CONFIG analysis_prefab_config = {
            side,
            APC_LEVEL_DRUNK
        };
        COR_INDEXER cor_indexer = GetCoreAnalysisResult(board, analysis_prefab_config);
        board[cor_indexer.i][cor_indexer.j] = side * (i+21);
    }

    for (int i = 0; i < COR_BOARD_SIZE; ++i) {
        for (int j = 0; j < COR_BOARD_SIZE; ++j) {
            (j == COR_BOARD_SIZE-1) ? printf("%4d\n", board[i][j]) : printf("%4d,", board[i][j]);
        }
    }

    return 0;
}
