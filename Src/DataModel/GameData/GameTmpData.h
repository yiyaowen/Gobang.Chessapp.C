#ifndef GAME_TMP_DATA_H
#define GAME_TMP_DATA_H

#include "ChessappDefinitions.h"
#include "Point.h"

#include <stdbool.h>

typedef struct type_GameTmpData {
    Side winner;
    Side currentActiveSide;
    Point currentSelectedPoint;
    bool isLastMoveConfirmed;
    bool* booleanGameBoard;
} GameTmpData;

GameTmpData* getNewGameTmpData();

void releaseGameTmpData(GameTmpData** data);

#endif // GAME_TMP_DATA_H