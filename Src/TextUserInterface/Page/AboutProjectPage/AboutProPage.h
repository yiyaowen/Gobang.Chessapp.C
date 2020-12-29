#ifndef ABOUT_PRO_PAGE_H
#define ABOUT_PRO_PAGE_H

#include "Route/Route.h"
#include "Page/Page.h"
#include "Page/PageOption.h"

typedef struct type_AboutProPageData {
    int selectedOption;
} AboutProPageData;

PAGE_FUNCTION_TEMPLATE(AboutPro)

Page* getNewAboutProPage();

void printAboutProPageNormalContent();
void printAboutProPageEasterEgg1Content();
void printAboutProPageEasterEgg2Content();

PageOptionID getValidAboutProPageOptionFromUser();

#define ABOUTPRO_PAGE_OPTION_NUM    3

#define ABOUTPRO_PAGE_OPTION_ID_ABOUTPRO    PAGE_ID_ABOUTPRO
#define ABOUTPRO_PAGE_OPTION_ID_PREVIOUS        51
#define ABOUTPRO_PAGE_OPTION_ID_NORMAL          52
#define ABOUTPRO_PAGE_OPTION_ID_EASTEREGG1      53
#define ABOUTPRO_PAGE_OPTION_ID_EASTEREGG2      54

#define ABOUT_PROJECT_NORMAL_CONTENT \
    "  `Gobang.Chessplayer.C` is a small and light project for building a cross-platform" "\n" \
    "gobang game program in console and terminal. As the name suggests, this project is " "\n" \
    "based on C language. Building on different platforms is easy with CMake tool. There" "\n" \
    "is no plan to continue extending this program since it is only a little practice.  " "\n" \
    "In fact, I prefer to call it a cool toy instead a program.                         " "\n" \
    "  Enjoy yourself! Nothing is more beautiful than our life right now.               " "\n"

#define ABOUT_PROJECT_EASTER_EGG_1_CONTENT \
    "  Congratulations! You have found one of the easter eggs in 'About Project' page.  " "\n" \
    "Now you can relax for a while. (I won't tell you that there's another easter egg)  " "\n"

#define ABOUT_PROJECT_EASTER_EGG_2_CONTENT \
    "  The last trace of steam evaporated in the autumn air. The train rounded a corner." "\n" \
    "Harry’s hand was still raised in farewell.                                         " "\n" \
    "  “He’ll be alright,” murmured Ginny.                                              " "\n" \
    "  As Harry looked at her, he lowered his hand absentmindedly and touched the     " "\n" \
    "lightning scar on his forehead.                                                    " "\n" \
    "  “I know he will.”                                                                " "\n" \
    "  The scar had not pained Harry for nineteen years. All was well.                  " "\n"

#endif // ABOUT_PRO_PAGE_H