#include "DataComparison.h"

int intAscendingOrder(const void* first, const void* second)
{
    return *(int*)first - *(int*)second;
}