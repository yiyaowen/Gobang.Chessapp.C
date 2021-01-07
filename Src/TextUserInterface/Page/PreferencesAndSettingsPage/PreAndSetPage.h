#ifndef PRE_AND_SET_PAGE_H
#define PRE_AND_SET_PAGE_H

#include "Route/Route.h"
#include "Page/Page.h"
#include "Page/PageOption.h"

typedef struct type_PreAndSetPageData {
    int totalOptionCount;
    PageOptionID selectedOption;
} PreAndSetPageData;

PAGE_FUNCTION_TEMPLATE(PreAndSet)

Page* getNewPreAndSetPage();

#define PREANDSET_OPTION_NUM   3

#define PREANDSET_PAGE_OPTION_ID_PREANDSET  PAGE_ID_PREANDSET
#define PREANDSET_PAGE_OPTION_ID_PREVIOUS       31
#define PREANDSET_PAGE_OPTION_ID_MUSICSOUND     32
#define PREANDSET_PAGE_OPTION_ID_NETWORKCONFIG  33

#define PREANDSET_PAGE_OPTION_NAME_PREVIOUS             "<1> Previous Page"
#define PREANDSET_PAGE_OPTION_NAME_MUSICSOUND_ON        "<2> Music & Sound / On"
#define PREANDSET_PAGE_OPTION_NAME_MUSICSOUND_OFF       "<2> Music & Sound / Off"
#define PREANDSET_PAGE_OPTION_NAME_NETWORKCONFIG_ON     "<3> Network Config / On"
#define PREANDSET_PAGE_OPTION_NAME_NETWORKCONFIG_OFF    "<3> Network Config / Off"

#endif // PRE_AND_SET_PAGE_H