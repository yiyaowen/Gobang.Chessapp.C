#ifndef LOCATION_H
#define LOCATION_H

typedef struct type_Location {
    char x;
    int y;
} Location;

Location makeLocation(char x, int y);

char* makeDescriptionStringFromLocation(Location location);

#define CHAR_COUNT_PER_LOCATION_DESC    4

#endif // LOCATION_H
