#ifndef PAGE_H
#define PAGE_H

#include "Route.h"
#include "PageID.h"

typedef struct type_PageData {
    PageID masterPageId;
    void* rawData;
} PageData;

PageData* getNewPageData();

typedef void (*PageDisplayFunction)(PageData*);
typedef Route* (*PageUpdateFunction)(PageData*, Route*);
typedef void (*PageReleaseFunction)(PageData**);

typedef struct type_Page {
    PageID id;
    char* name;
    char* desc;
    PageData* data;
    PageDisplayFunction displayFunc;
    PageUpdateFunction updateFunc;
    PageReleaseFunction releaseFunc;
} Page;

#define PAGE_FUNCTION_TEMPLATE(PAGE_NAME) \
void display ## PAGE_NAME ## Page(PageData* data); \
Route* update ## PAGE_NAME ## Page(PageData* data, Route* routePassBy ## PAGE_NAME); \
void release ## PAGE_NAME ## Page(PageData** data);

Page* getNewDefaultPage();

void releasePage(Page** page);

typedef struct type_PageStack {
    int count;
    Page** pages;
    const int capacity;
    Page* topPage;
} PageStack;

extern PageStack* globalTuiPageStack;
#define getGlobalTuiPageStack() (globalTuiPageStack)

PageStack* getNewPageStack();

void pushPageIntoPageStack(Page* page, PageStack* stack);

Route* handleTopPageInPageStack(PageStack* stack, Route* route);

Page* popPageFromPageStack(PageStack* stack);

void releasePageStack(PageStack** stack);

#endif // PAGE_H