#ifndef CORE_BOARD_H
#define CORE_BOARD_H

#include "CoreDefinitions.h"

#include <stdbool.h>

bool isCoreBoardFull(const CoreBoard board);

CorePoint getMaxScorePointInCoreScoreBoard(CoreScoreBoard board);

#endif // CORE_BOARD_H