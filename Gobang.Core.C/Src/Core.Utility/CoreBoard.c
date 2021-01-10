#include "CoreDefinitions.h"
#include "CoreBoard.h"
#include "CoreMathUtils.h"

#include <stdio.h>

bool isCoreBoardFull(const CoreBoard board)
{
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            if (board[i][j] == CORE_SIDE_EMPTY) return false;
        }
    }
    return true;
}

void* coreNoNullMalloc(size_t blockSize)
{
    void* target = malloc(blockSize);
    if (target)
        return target;
    printf("malloc null error.\n");
    exit(EXIT_FAILURE);
}