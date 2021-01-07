#include "Point.h"

#include <stdlib.h>

Point makePoint(int i, int j)
{
    Point point = { i, j };
    return point;
}

CorePoint makeCorePointFromPoint(Point point)
{
    CorePoint corePoint = { point.i, point.j };
    return corePoint;
}