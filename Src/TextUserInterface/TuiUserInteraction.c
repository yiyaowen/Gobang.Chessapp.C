#include "TuiUserInteraction.h"
#include "TuiUtility.h"
#include "SmartDisplay.h"

#include <stdio.h>

PageOptionID getValidPageOptionFromUser(PageID currentPageId, int currentPageOptionCount)
{
    char c;
    int selectedNum;

get_user_input:
    c = (char)getchar();
    if (c == '\n') {
        putCharBack(c);
        clearInputBuffer();
        return PAGE_OPTION_ID_CONFIRM;
    }
    else {
        selectedNum = (int)(c - '0');
        if (selectedNum > 0 && selectedNum <= currentPageOptionCount) {
            clearInputBuffer();
            return calculatePageOptionIdFromPageIdAndSelectedNum(currentPageId, selectedNum);
        }
        else {
            printWithDoubleBuffer(
                printf("No such option. Please choose from 1~%d, or press Enter.\n", currentPageOptionCount);
                printf(PROMPT);
            );
            clearInputBuffer();
            goto get_user_input;
        }
    }
}