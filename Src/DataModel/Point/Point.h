#ifndef POINT_H
#define POINT_H

#include "CoreDefinitions.h"

typedef struct type_Point {
    int i;
    int j;
} Point;

Point makePoint(int i, int j);

CorePoint makeCorePointFromPoint(Point point);

#define makeNullPoint() makePoint(-1, -1)
#define isPointNull(POINT) ((POINT).i == -1 && (POINT).j == -1)

#endif // POINT_H
