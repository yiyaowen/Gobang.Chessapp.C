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
    "   `Chessplayer` is the core of this gobang game program, i.e. 'C' in 'PvC'.        " "\n" \
    "   There are six game levels of `Chessplayer` in total: [Drunk], [Low], [Middle],   " "\n" \
    " [High], [Invincible] and [Random]. [Drunk] means that `Chessplayer` will choose its" "\n" \
    " position randomly, just like a drunkard. From [Low] to [Invincible], the game will " "\n" \
    " be more and more difficult to win. [Random] doesn't mean that `Chessplayer` will   " "\n" \
    " choose position randomly. Instead, the core program will choose a level randomly   " "\n" \
    " for you. That's kind of interesting since you don't know the true game level.      " "\n" \
    "   Enjoy yourself! Why not have a try right now.                                    " "\n"

#endif // ABOUT_CHE_PAGE_H