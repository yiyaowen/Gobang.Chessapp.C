#include "ChessappDefinitions.h"
#include "Page.h"

#include <stdlib.h>
#include <stdbool.h>

PageData* getNewPageData()
{
    PageData* data = malloc(sizeof(PageData));
    data->masterPageId = PAGE_ID_DEFAULT;
    data->rawData = NULL;
    return data;
}

Page* getNewDefaultPage()
{
    Page* page = malloc(sizeof(Page));
    page->id = PAGE_ID_DEFAULT;
    page->name = NULL;
    page->desc = NULL;
    page->data = NULL;
    page->displayFunc = NULL;
    page->updateFunc = NULL;
    page->releaseFunc = NULL;
    return page;
}

void releasePage(Page** page)
{
    (*page)->releaseFunc(&((*page)->data));
    free(*page);
    *page = NULL;
}

PageStack* globalTuiPageStack;

PageStack* getNewPageStack()
{
    PageStack* stack = malloc(sizeof(PageStack));
    stack->count = 0;
    stack->capacity = PAGE_STACK_CAPACITY;
    stack->pages = (Page**)malloc(sizeof(Page*)*(stack->capacity));
    stack->topPage = NULL;
    return stack;
}

void pushPageIntoPageStack(Page* page, PageStack* stack)
{
    if (stack->count < stack->capacity) {
        stack->topPage = stack->pages[(stack->count)++] = page;
    }
    else {
        abortWithMsg("Page stack overflow! Too many pages in page stack.");
    }
}

Route* handleTopPageInPageStack(PageStack* stack, Route* route)
{
    while (true) {
        Page* topPage = stack->topPage;
        topPage->displayFunc(topPage->data);
        route = topPage->updateFunc(topPage->data, route);
        if (isRouteOver(route)) {
            route->status = ROUTE_CONTINUE;
            return route;
        }
    }
}

Page* popPageFromPageStack(PageStack* stack)
{
    if (stack->count > 0) {
        --stack->count;
        stack->topPage = stack->pages[(stack->count-1) > 0 ? (stack->count-1) : 0];
        return stack->pages[stack->count];
    }
    else {
        abortWithMsg("Page stack underflow! Page stack holds at least 0 page.");
    }
}

void releasePageStack(PageStack** stack)
{
    while ((*stack)->count > 0) {
        Page* pageToRelease = popPageFromPageStack(*stack);
        releasePage(&pageToRelease);
    }
    free((*stack)->pages);
    free(*stack);
    *stack = NULL;
}