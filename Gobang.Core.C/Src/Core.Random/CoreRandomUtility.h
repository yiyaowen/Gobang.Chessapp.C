#ifndef CORE_RANDOM_UTILITY_H
#define CORE_RANDOM_UTILITY_H

#include "CoreDefinitions.h"

int filterValidPointsFromCoreBoard(const CoreBoard board, CorePoint* validPoints);

int getRandomIntFromLeftInclusiveRange(int left, int right);

#endif // CORE_RANDOM_UTILITY_H
