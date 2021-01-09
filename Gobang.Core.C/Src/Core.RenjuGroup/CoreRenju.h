#ifndef CORE_RENJU_H
#define CORE_RENJU_H

#include "CoreRenjuPattern.h"

typedef struct type_Renju {
    RenjuPattern blackPattern;
    RenjuPattern whitePattern;
} Renju;

Renju* getNewRenju();

void releaseRenju(Renju** renju);

#endif // CORE_RENJU_H