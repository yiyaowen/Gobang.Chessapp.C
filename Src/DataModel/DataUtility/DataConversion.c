#include "ChessappDefinitions.h"
#include "DataConversion.h"

Point makePointFromLocation(Location location)
{
    Point point = { BOARD_SIZE-location.x, location.y-'A' };
    return point;
}

Location makeLocationFromPoint(Point point)
{
    Location location = { BOARD_SIZE-point.i, (char)(point.j+'A') };
    return location;
}