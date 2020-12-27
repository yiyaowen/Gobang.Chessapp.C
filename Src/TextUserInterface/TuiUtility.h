#ifndef TUI_UTILITY_H
#define TUI_UTILITY_H

#include "TuiDefinitions.h"

#include <stdio.h>

#define printSpaces(spacesNum) do { \
    printf("%" #spacesNum "s", ""); \
} while (0)

// Before using this you must make sure [stdin] is not empty,
// otherwise there will be an unexpected stop. One solution is
// calling [putCharBack] after getting a '\n' from [stdin].
#define clearInputBuffer() do { \
    char tmp; \
    while ((tmp = getchar()) != '\n' && tmp != EOF) ; \
} while (0)

#define putCharBack(c) do { \
    ungetc(c, stdin); \
} while (0)

#define printOption(NAME, ID, SELECTED_ID) do { \
    printSpaces(20); \
    if (ID == SELECTED_ID) { \
        printf(BLUE_TEXT(HIGHLIGHT_TEXT(SELECT_ARROW))); \
        printSpaces(2); \
        if (ID == HOME_PAGE_OPTION_ID_EXIT) { \
            printf(RED_TEXT(HIGHLIGHT_TEXT(UNDERLINE_TEXT("%s"))), NAME); \
        } \
        else { \
            printf(HIGHLIGHT_TEXT(UNDERLINE_TEXT("%s")), NAME); \
        } \
    } \
    else { \
        printSpaces(5); \
        printf("%s", NAME); \
    } \
    printf("\n\n"); \
} while (0)

#endif // TUI_UTILITY_H