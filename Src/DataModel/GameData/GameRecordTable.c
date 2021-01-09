#include "GameRecordTable.h"

#include <stdbool.h>

GameRecordTable* getNewGameRecordTable()
{
    GameRecordTable* table = (GameRecordTable*)malloc(sizeof(GameRecordTable));
    table->maxRecordStepCount = BOARD_SIZE * BOARD_SIZE;
    table->totalMoveCount = 0;
    table->moveHistoryArray = (Point*)malloc(sizeof(Point)*table->maxRecordStepCount);
    return table;
}

void addNewMoveToGameRecordTable(Side moveSide, Point movePoint, GameRecordTable* recordTable)
{
    if (recordTable->totalMoveCount < recordTable->maxRecordStepCount) {
        recordTable->moveHistoryArray[(recordTable->totalMoveCount)++] = movePoint;
    }
}

Point getLastMovePointInGameRecordTable(GameRecordTable* recordTable)
{
    if (recordTable->totalMoveCount == 0) return makeNullPoint();
    return (recordTable->moveHistoryArray)[recordTable->totalMoveCount-1];
}

Point getNearestNthMovePointOfSideInGameRecordTable(int nth, Side whichSide, GameRecordTable* recordTable)
{
    bool isLastPieceBlack = ((recordTable->totalMoveCount % 2) != 0);
    int offsetToEnd = (!(isLastPieceBlack ^ isBlackSide(whichSide)) ? 2 * nth : 2 * nth + 1);
    return (recordTable->moveHistoryArray)[recordTable->totalMoveCount - 1 - offsetToEnd];
}

void releaseGameRecordTable(GameRecordTable** table)
{
    free((*table)->moveHistoryArray);
    free(*table);
    *table = NULL;
}