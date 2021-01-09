#include "ChessappDefinitions.h"
#include "DataConversion.h"

Point makePointFromLocation(Location location)
{
    Point point = { BOARD_SIZE-location.y, location.x-'A' };
    return point;
}

Location makeLocationFromPoint(Point point)
{
    Location location = { (char)(point.j+'A'), BOARD_SIZE-point.i };
    return location;
}