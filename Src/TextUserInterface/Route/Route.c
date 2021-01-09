#include "Route.h"

Route* getNewDefaultRoute()
{
    Route* route = malloc(sizeof(Route));
    route->status = ROUTE_CONTINUE;
    route->exitStatus = ROUTE_EXIT_SUCCESS;
    return route;
}

bool isRouteOver(Route* route)
{
    return route->status == ROUTE_OVER;
}

bool isRouteSuccess(Route* route)
{
    return route->exitStatus == ROUTE_EXIT_FAILURE;
}

void releaseRoute(Route* route)
{
    free(route);
}