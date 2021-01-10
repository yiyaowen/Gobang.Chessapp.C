#ifndef ABOUT_CHE_PAGE_H
#define ABOUT_CHE_PAGE_H

#include "Route.h"
#include "Page.h"
#include "PageOption.h"

typedef struct type_AboutChePageData {
    void* reserved;
} AboutChePageData;

PAGE_FUNCTION_TEMPLATE(AboutChe)

Page* getNewAboutChePage();

void printAboutChePageContent();

#define ABOUT_CHESSPLAYER_CONTENT \
    "   " HIGHLIGHT_TEXT(UNDERLINE_TEXT("`Chessplayer`")) " is the core of this gobang game program, i.e. 'C' in 'PvC'." "\n\n" \
    "   There are total 6 gobang game levels: " GREEN_TEXT(HIGHLIGHT_TEXT("[Drunk]")) ", " GREEN_TEXT(HIGHLIGHT_TEXT("[Low]")) \
    ", " GREEN_TEXT(HIGHLIGHT_TEXT("[Middle]")) ", " GREEN_TEXT(HIGHLIGHT_TEXT("[High]")) ", " GREEN_TEXT(HIGHLIGHT_TEXT("[Random]")) "." "\n\n" \
    " " GREEN_TEXT(HIGHLIGHT_TEXT("[Drunk]")) ": `Chessplayer` will choose its move position randomly just like a drunkard." "\n\n" \
    " " GREEN_TEXT(HIGHLIGHT_TEXT("[Low] - [High]")) ": The game will be more and more difficult to win.                   " "\n\n" \
    " " GREEN_TEXT(HIGHLIGHT_TEXT("[Random]")) ": This doesn't mean the machine will choose position randomly. Instead, the" "\n" \
    " core program will choose a game level randomly for you. That's kind of interesting." "\n\n" \
    "   Enjoy yourself! Why not have a try right now.                                    " "\n"

#endif // ABOUT_CHE_PAGE_H