#ifndef GAME_RECORD_TABLE_H
#define GAME_RECORD_TABLE_H

#include "Point/Point.h"
#include "ChessappDefinitions.h"

typedef struct type_GameRecordTable {
    int maxRecordStepCount;
    int totalMoveCount;
    Point* moveHistoryArray;
} GameRecordTable;

GameRecordTable* getNewGameRecordTable();

void addNewMoveToGameRecordTable(Side moveSide, Point movePoint, GameRecordTable* recordTable);

Point getLastMovePointInGameRecordTable(GameRecordTable* recordTable);

Point getNearestNthMovePointOfSideInGameRecordTable(int nth, Side whichSide, GameRecordTable* recordTable);

void releaseGameRecordTable(GameRecordTable** table);

#endif // GAME_RECORD_TABLE_H