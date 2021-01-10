#include "Location.h"
#include "ChessappDefinitions.h"

#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable:4996)

Location makeLocation(char x, int y)
{
    Location location = { x, y };
    return location;
}

char* makeDescriptionStringFromLocation(Location location)
{
    char* desc = (char*)noNullMalloc(sizeof(char)*(CHAR_COUNT_PER_LOCATION_DESC + 1));
    sprintf(desc, "%c,%2d", location.x, location.y);
    return desc;
}
