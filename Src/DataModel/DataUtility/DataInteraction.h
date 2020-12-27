#ifndef DATA_INTERACTION_H
#define DATA_INTERACTION_H

#include "GameData/GameRecordTable.h"

#include <stdbool.h>

bool exportGameRecordTableToFile(GameRecordTable* table, const char * path);

#endif // DATA_INTERACTION_H