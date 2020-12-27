#include "Location.h"

#include <stdlib.h>
#include <stdio.h>

Location makeLocation(char x, int y)
{
    Location location = { x, y };
    return location;
}

char* makeDescriptionStringFromLocation(Location location)
{
    char* desc = (char*)malloc(sizeof(char)*(CHAR_COUNT_PER_LOCATION_DESC + 1));
    sprintf(desc, "%c,%2d", location.x, location.y);
    return desc;
}
