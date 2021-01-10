#include "CoreDefinitions.h"
#include "CoreBoard.h"
#include "CoreMathUtils.h"

bool isCoreBoardFull(const CoreBoard board)
{
    for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
        for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
            if (board[i][j] == CORE_SIDE_EMPTY) return false;
        }
    }
    return true;
}