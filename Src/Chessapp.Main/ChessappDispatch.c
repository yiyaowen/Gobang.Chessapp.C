#include "ChessappDispatch.h"

Route* startRoutine(PageStack* stack, Page* page, Route* route)
{
    pushPageIntoPageStack(page, stack);
    route = handleTopPageInPageStack(stack, route);
    Page* pageToRelease = popPageFromPageStack(stack);
    releasePage(&pageToRelease);
    return route;
}