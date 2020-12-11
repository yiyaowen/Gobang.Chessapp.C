#ifndef INCLUDE_CHE_TUI_H
#define INCLUDE_CHE_TUI_H

#include "CheDef.h"

////////////////
// Global TUI //
////////////////

typedef struct {
    int status;
    int exit_status;
} Route;

/**
 * Get default route.
 *
 * @param route (Route to be initialiazed)
 * @return
 */
void InitRoute(Route *route);

typedef void *PageInfo;

typedef struct {
   int id;
   char *name;
   char *desc;
   PageInfo page_info;
   void(*pfnDisplayer)(PageInfo);
   Route *(*pfnHandler)(Route *, PageInfo);
} Page;
    
#define PAGE_STACK_CAPACITY 10
typedef struct {
    Page *pages[PAGE_STACK_CAPACITY];
    int count;
    Page *pTopPage;
} PageStack;

/**
 * Start a routine.
 *
 * @param pNewPage (The new page to display)
 * @param route (Route information for [pNewPage])
 * @return route_ (Route information from [pNewPage])
 */
Route *StartRoutine(Page *pNewPage, Route *route);

/**
 * Push a page to [PageStack].
 *
 * @param pNewPage (The new page to push)
 * @return
 */
void PushPage(Page *pNewPage);

/**
 * Call handler of top page.
 *
 * @param route (Route information for top page)
 * @return route_ (Route information from top page)
 */
Route *HandlePage(Route *route);

/**
 * Pop a page from [PageStack].
 *
 * @param
 * @return
 */
void PopPage();

///////////////////
// Page template //
///////////////////

/*
typedef struct {

} *####PageInfo;

void Init####PageInfo(####PageInfo info);

void Init####Page(Page *####_page);

void Display####Page(PageInfo page_info);

Route *Handle####Page(Route *route, PageInfo page_info);
*/

///////////////
// TUI Utils //
///////////////

/**
 * Get a valid option.
 *
 * @param iBaseOption (Code of base option)
 * @param iOptionCount (Total options count)
 * @return iOption (A valid option)
 */
int GetValidOption(int iBaseOption, int iOptionCount);

//////////////
// Home TUI //
//////////////

typedef struct {
    int iOptionCount;
    int iOptionSelected;
} *HomePageInfo, HomePageInfoType;
void InitHomePageInfo(HomePageInfo info);
void InitHomePage(Page *home_page);
void DisplayHomePage(PageInfo page_info);
Route *HandleHomePage(Route *route, PageInfo page_info);

//////////////
// Game TUI //
//////////////

typedef struct {
    GAME_PREFAB_CONFIG game_prefab_config;
} *GamePageInfo, GamePageInfoType;
void InitGamePageInfo(GamePageInfo info);
void InitGamePage(Page *game_page);
void InitPvPPage(Page *pvp_page);
void InitPvCPage(Page *pvc_page);
void DisplayGamePage(PageInfo page_info);
Route *HandleGamePage(Route *route, PageInfo page_info);

/**
 * Display chessboard.
 *
 * @param pos (Position selected, and it will highlighted)
 * @return
 */
void DisplayBoard(POSITION pos);

/**
 * Start a PvP game.
 *
 * @param route (Route from [HandleGamePage])
 * @param game_prefab_config (Game's prefabricated configuration)
 * @return route_ (Route after handled)
 */
Route *StartPvP(Route *route, GAME_PREFAB_CONFIG game_prefab_config);

/**
 * Start a PvC game.
 *
 * @param route (Route from [HandleGamePage])
 * @param game_prefab_config (Game's prefabricated configuration)
 * @return route_ (Route after handled)
 */
Route *StartPvC(Route *route, GAME_PREFAB_CONFIG game_prefab_config);

/* iRound */
#define ROUND_BLACK         1
#define ROUND_WHITE         2

/**
 * Display input hint for the specific side.
 *
 * @param iRound (ROUND_WHITE or ROUND_BLACK)
 * @return
 */
void PrintHint(int iRound);

/**
 * Loop until get a valid input for Chessboard position.
 *
 * @param iRound (ROUND_WHITE or ROUND_BLACK)
 * @param pos (The position that has been selected)
 * @return pos_ (The valid position from user input)
 */
POSITION GetValidPosition(int iRound, POSITION pos);

/**
 * Check if the option is a special control option.
 *
 * @param key (The option to be checked)
 * @return (If it is a special control option return 1, otherwise return 0)
 */
int IsSpecialControlOption(char key);

/**
 * Handle special control options when playing.
 *
 * @param key (The special control option)
 * @param inPos (The position that will be modified)
 * @return
 */
void HandleControlOption(char key, POSITION * inPos);

/**
 * Check if pos is a valid Chessboard position.
 *
 * @param pos (The position to be checked)
 * @return iErrorType (If pos is valid return POS_VALID, otherwise return specific error type)
 */
int IsPositionValid(POSITION pos);

/* iErrorType */
#define POS_VALID           0
#define POS_OUT_OF_BOARD        1
#define POS_OVERLAPPED          2
#define POS_BAD_FORMAT          3

/**
 * Display error hint of the specific error type.
 *
 * @param iErrorType (The type of input error)
 * @return
 */
void PrintErrorHint(int iErrorType);

///////////////////
// PreAndSet TUI //
///////////////////

typedef struct {
    int iOptionCount;
    int iOptionSelected;
} *PreAndSetPageInfo, PreAndSetPageInfoType;
void InitPreAndSetPageInfo(PreAndSetPageInfo info);
void InitPreAndSetPage(Page *pre_and_set_page);
void DisplayPreAndSetPage(PageInfo page_info);
Route *HandlePreAndSetPage(Route *route, PageInfo page_info);

/**
 * Print options of "Preferences & Settings" page.
 *
 * @param iOption (The option selected now, and it will be highlighted)
 * @return
 */
void PrintPreAndSetOptions(int iOption);

/**
 * Print single option of "Preferences & Settings" page.
 *
 * @param iOption (The option selected now)
 * @param iOptionNum (The number code of option)
 * @param szOptionText (The text of option)
 * @return
 */
void PrintPreAndSetOption(int iOption, int iOptionNum, const char *szOptionText);

//////////////////
// AboutChe TUI //
//////////////////

typedef struct {
    void* reserved;
} *AboutChePageInfo, AboutChePageInfoType;
void InitAboutChePageInfo(AboutChePageInfo info);
void InitAboutChePage(Page *about_che_page);
void DisplayAboutChePage(PageInfo page_info);
Route *HandleAboutChePage(Route *route, PageInfo page_info);

/**
 * Print content of "About Chessplayer" page.
 *
 * @param
 * @return
 */
void PrintAboutCheContent();

//////////////////
// AboutPro TUI //
//////////////////

typedef struct {
    int iOptionSelected;
} *AboutProPageInfo, AboutProPageInfoType;
void InitAboutProPageInfo(AboutProPageInfo info);
void InitAboutProPage(Page *about_pro_page);
void DisplayAboutProPage(PageInfo page_info);
Route *HandleAboutProPage(Route *route, PageInfo page_info);

/**
 * Print content of "About Project" page.
 *
 * @param
 * @return
 */
void PrintAboutProContent();
void PrintAboutProEasterEgg1Content();
void PrintAboutProEasterEgg2Content();

/**
 * Get valid option for "About Project" page.
 *
 * @param
 * @return iOption (The valid option for "About Project" page)
 */
int GetValidAboutProOption();

#endif /* INCLUDE_CHE_TUI_H */
