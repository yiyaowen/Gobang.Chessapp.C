#include "DataInteraction.h"

bool exportGameRecordTableToFile(GameRecordTable* table, const char* path)
{
    Point point;
    Side side = SIDE_BLACK;
    FILE * fileHandle = fopen(path, "w");
    if (fileHandle == NULL) return false;

    Side board[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = SIDE_EMPTY;
        }
    }
    for (int i = 0; i < table->totalMoveCount; ++i) {
        point = table->moveHistoryArray[i];
        board[point.i][point.j] = (i + 1) * side;
        reverseSide(side);
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE-1; ++j) {
            fprintf(fileHandle, "%d ", board[i][j]);
        }
        fprintf(fileHandle, "%d\n", board[i][BOARD_SIZE-1]);
    }

    fclose(fileHandle);
    return true;
}