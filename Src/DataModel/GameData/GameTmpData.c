#include "GameTmpData.h"

#include <string.h>

GameTmpData* getNewGameTmpData()
{
    GameTmpData* data = (GameTmpData*)malloc(sizeof(GameTmpData));
    data->winner = SIDE_EMPTY;
    data->currentActiveSide = SIDE_BLACK;
    data->currentSelectedPoint = makePoint(0, 0);
    data->isLastMoveConfirmed = false;
    data->booleanGameBoard = (bool*)malloc(sizeof(bool)* BOARD_SIZE * BOARD_SIZE);
    memset(data->booleanGameBoard, false, BOARD_SIZE * BOARD_SIZE);
    return data;
}

void releaseGameTmpData(GameTmpData** data)
{
    free((*data)->booleanGameBoard);
    free(*data);
    *data = NULL;
}