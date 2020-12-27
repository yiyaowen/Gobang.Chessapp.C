#ifndef ROUTE_H
#define ROUTE_H

#include <stdlib.h>
#include <stdbool.h>

typedef int RouteStatus;
#define ROUTE_OVER          1
#define ROUTE_CONTINUE      2

typedef int RouteExitStatus;
#define ROUTE_EXIT_SUCCESS      EXIT_SUCCESS
#define ROUTE_EXIT_FAILURE      EXIT_FAILURE

typedef struct type_Route {
    RouteStatus status;
    RouteExitStatus exitStatus;
} Route;

Route* getNewDefaultRoute();

bool isRouteOver(Route* route);
bool isRouteSuccess(Route* route);

void releaseRoute(Route* route);

#endif // ROUTE_H