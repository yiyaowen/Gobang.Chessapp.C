#include "ChessappDispatch.h"

void* noNullMalloc(Size blockSize)
{
    void* target = malloc(blockSize);
    if (target)
        return target;
    abortWithMsg("[malloc]: Memory alloc failed.");
}

Route* startRoutine(PageStack* stack, Page* page, Route* route)
{
    pushPageIntoPageStack(page, stack);
    route = handleTopPageInPageStack(stack, route);
    Page* pageToRelease = popPageFromPageStack(stack);
    releasePage(&pageToRelease);
    return route;
}