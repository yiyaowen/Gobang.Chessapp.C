#ifndef DATA_CONVERSION_H
#define DATA_CONVERSION_H

#include "Point.h"
#include "Location.h"

Point makePointFromLocation(Location location);
Location makeLocationFromPoint(Point point);

#endif // DATA_CONVERSION_H
