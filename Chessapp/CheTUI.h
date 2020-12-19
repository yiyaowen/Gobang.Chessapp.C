#ifndef CHE_TUI_H
#define CHE_TUI_H

#include "CheDef.h"

#define PAGE_TEMPLATE(PAGE_NAME) \
void Display ## PAGE_NAME ## Page(PageInfo info); \
Route* Handle ## PAGE_NAME ## Page(Route* route, PageInfo info);

typedef struct {
    int status;
    int exit_status;
} Route;

Route* GetDefaultRoute();

typedef void *PageInfo;

typedef struct {
   int id;
   char *name;
   char *desc;
   PageInfo info;
   void(*pfnDisplayer)(PageInfo);
   Route*(*pfnHandler)(Route*, PageInfo);
} Page;

#define PAGE_STACK_CAPACITY 10
typedef struct {
    Page* pages[PAGE_STACK_CAPACITY];
    int count;
    Page* top_page;
} PageStack;

/**
 * Start a routine of specific page.
 *
 * @param page
 * @param route
 * @return route_
 */
Route* StartRoutine(Page* page, Route* route);

/**
 * Push a page into page stack.
 * If stack is full, program exits with abort message.
 *
 * @param page
 */
void PushPage(Page* page);

/**
 * Call top page's handler function.
 *
 * @param route
 * @return route_
 */
Route* HandleTopPage(Route* route);

/**
 * Pop a page from page stack.
 * If stack is empty, program exits with abort message.
 */
void PopPage();

/**
 * Get a valid option from user input.
 *
 * @param iBaseOption (Current page's base option code)
 * @param iOptionCount
 * @return iValidOption
 */
int GetValidOptionFromUser(int iBaseOption, int iOptionCount);

PAGE_TEMPLATE(Home)
PAGE_TEMPLATE(Game)
PAGE_TEMPLATE(PreAndSet)
PAGE_TEMPLATE(AboutChe)
PAGE_TEMPLATE(AboutPro)

// Home page
typedef struct {
    int iOptionCount;
    int iOptionSelected;
} *HomePageInfo, HomePageInfoType;

Page* GetDefaultHomePage();

// Game page
typedef struct {
    GAME_PREFAB_CONFIG game_prefab_config;
} *GamePageInfo, GamePageInfoType;

void DisplayBoard(POSITION pos);

Route* StartPvP(Route* route, GAME_PREFAB_CONFIG game_prefab_config);
Route* StartPvC(Route* route, GAME_PREFAB_CONFIG game_prefab_config);

Page* GetDefaultPvPPage();
Page* GetDefaultPvCPage();

#define ROUND_BLACK         1
#define ROUND_WHITE         2

void PrintHint(int iRound);

/**
 * Get a valid chessboard position from user input.
 *
 * @param iRound (ROUND_BLACK or ROUND_WHITE)
 * @param pos (Last position selected)
 * @return pos_
 */
POSITION GetValidPositionFromUser(int iRound, POSITION pos);

int IsSpecialControlOption(char key);

void HandleControlOption(char key, POSITION *pos);

int IsPositionValid(POSITION pos);

#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

void PrintErrorHint(int iErrorType);

// PreAndSet page: Preferences & Settings
typedef struct {
    int iOptionCount;
    int iOptionSelected;
} *PreAndSetPageInfo, PreAndSetPageInfoType;

void PrintPreAndSetOptions(int iOption);

void PrintPreAndSetOption(int iOption, int iOptionNum, const char *szOptionText);

Page* GetDefaultPreAndSetPage();

// AboutChe page: About Chessplayer
typedef struct {
    void* reserved;
} *AboutChePageInfo, AboutChePageInfoType;

void PrintAboutCheContent();

Page* GetDefaultAboutChePage();

// AboutPro page: About Project
typedef struct {
    int iOptionSelected;
} *AboutProPageInfo, AboutProPageInfoType;

void PrintAboutProNormalContent();
void PrintAboutProEasterEgg1Content();
void PrintAboutProEasterEgg2Content();

int GetValidAboutProOptionFromUser();

Page* GetDefaultAboutProPage();

#endif // CHE_TUI_H
