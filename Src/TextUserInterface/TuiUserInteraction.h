#ifndef TUI_USER_INTERACTION_H
#define TUI_USER_INTERACTION_H

#include "PageID.h"
#include "PageOption.h"

PageOptionID getValidPageOptionFromUser(PageID currentPageId, int currentPageOptionCount);

#endif // TUI_USER_INTERACTION_H