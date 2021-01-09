#include "GameTmpData.h"

#include <string.h>

GameTmpData* getNewGameTmpData()
{
    GameTmpData* data = (GameTmpData*)malloc(sizeof(GameTmpData));
    data->winner = SIDE_EMPTY;
    data->currentActiveSide = SIDE_BLACK;
    data->currentSelectedPoint = makeNullPoint();
    data->lastSelectedPoint = makeNullPoint();
    data->isLastMoveConfirmed = false;
    data->shouldUpdateTuiInformation = true;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            data->piecesGameBoard[i][j] = SIDE_EMPTY;
        }
    }
    return data;
}

void addNewMoveToGameTmpData(Side moveSide, Point movePoint, GameTmpData* tmpData)
{
    (tmpData->piecesGameBoard)[movePoint.i][movePoint.j] = moveSide;
}

void releaseGameTmpData(GameTmpData** data)
{
    free(*data);
    *data = NULL;
}