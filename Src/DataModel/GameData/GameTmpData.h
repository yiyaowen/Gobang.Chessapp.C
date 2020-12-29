#ifndef GAME_TMP_DATA_H
#define GAME_TMP_DATA_H

#include "ChessappDefinitions.h"
#include "Point/Point.h"

#include <stdbool.h>

typedef struct type_GameTmpData {
    Side winner;
    Side currentActiveSide;
    Point currentSelectedPoint;
    bool isLastMoveConfirmed;
    Side piecesGameBoard[BOARD_SIZE][BOARD_SIZE];
} GameTmpData;

GameTmpData* getNewGameTmpData();

void addNewMoveToGameTmpData(Side moveSide, Point movePoint, GameTmpData* tmpData);

void releaseGameTmpData(GameTmpData** data);

#endif // GAME_TMP_DATA_H