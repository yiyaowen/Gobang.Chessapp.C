#include "CoreRenju.h"
#include "CoreRenjuPattern.h"

#include <stdlib.h>

Renju* getNewRenju()
{
    Renju* renju = (Renju*)malloc(sizeof(Renju));
    renju->blackPattern = renju->whitePattern = RENJU_PATTERN_EMPTY;
    return renju;
}

void releaseRenju(Renju** renju)
{
    free(*renju);
    *renju = NULL;
}
