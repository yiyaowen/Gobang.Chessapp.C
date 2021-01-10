#include "CoreRenju.h"
#include "CoreRenjuPattern.h"
#include "CoreDefinitions.h"

#include <stdlib.h>

Renju* getNewRenju()
{
    Renju* renju = (Renju*)coreNoNullMalloc(sizeof(Renju));
    renju->blackPattern = renju->whitePattern = renju->banPattern = RENJU_PATTERN_EMPTY;
    return renju;
}

void releaseRenju(Renju** renju)
{
    free(*renju);
    *renju = NULL;
}
