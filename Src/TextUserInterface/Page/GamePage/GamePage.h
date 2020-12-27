#ifndef GAME_PAGE_H
#define GAME_PAGE_H

#include "ChessappDefinitions.h"
#include "Route.h"
#include "Page.h"
#include "PageOption.h"
#include "Point/Point.h"
#include "RenjuGroup/RenjuGroup.h"
#include "GameData/GamePrefabConfig.h"
#include "GameData/GameRecordTable.h"
#include "GameData/GameTmpData.h"
#include "AttributedString/AttributedString.h"

typedef struct type_GamePageSceneTui {
    AttributedString* string;
} GamePageSceneTUi;

typedef struct type_GamePageData {
    GamePrefabConfig* prefabConfig;
    GameRecordTable* recordTable;
    RenjuGroupList* renjuGroupList;
    GameTmpData* tmpData;
    GamePageSceneTUi* sceneTui;
} GamePageData;

GamePageSceneTUi* getNewGamePageSceneTui();

void drawNewPieceAtPointInGamePageSceneTui(Side whichSide, Point whichPoint, Point lastPoint, GamePageSceneTUi* tui);

void updateGameInformationInGamePageSceneTui(GamePageData* data, GamePageSceneTUi* tui);

void printGamePageSceneTui(GamePageSceneTUi* tui);

void releaseGamePageSceneTui(GamePageSceneTUi** tui);

PAGE_FUNCTION_TEMPLATE(Game)

Page* getNewGamePage(GamePrefabConfig* prefabConfig);

void printInputHint(Side side);

Point getValidMovePointFromUser(Route* route, GamePageData* data);

bool isSpecialControlOption(char key);

void handleSpecialControlOption(char key, Route* route, GamePageData* data);

typedef int InputErrorType;
#define INPUT_ERROR_TYPE_VALID          0
#define INPUT_ERROR_TYPE_OUT_OF_BOARD       1
#define INPUT_ERROR_TYPE_OVERLAPPED         2
#define INPUT_ERROR_TYPE_BAD_FORMAT         3

InputErrorType getErrorTypeOfMovePoint(Point point, GamePageData* data);

void printInputErrorHint(InputErrorType errorType);

#define GAME_PAGE_SCENE_RAW_TEXT \
  "//===>===>===>===>===>\\\\  15 ┏ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┯ ┓  //===>===>===>===>===>\\\\" "\n" \
    "||    Black  Piece    ||  14 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    White  Piece    ||" "\n" \
    "||                    ||  13 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||                    ||" "\n" \
    "||  Current - (x, x)  ||  12 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||  Current - (x, x)  ||" "\n" \
    "||                    ||  11 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||                    ||" "\n" \
    "|| Last step - (x, x) ||  10 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  || Last step - (x, x) ||" "\n" \
    "||                    ||   9 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||                    ||" "\n" \
    "|| More Move History: ||   8 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  || More Move History: ||" "\n" \
    "||    1.  ( x, x )    ||   7 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    1.  ( x, x )    ||" "\n" \
    "||    2.  ( x, x )    ||   6 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    2.  ( x, x )    ||" "\n" \
    "||    3.  ( x, x )    ||   5 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    3.  ( x, x )    ||" "\n" \
    "||    4.  ( x, x )    ||   4 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    4.  ( x, x )    ||" "\n" \
    "||    5.  ( x, x )    ||   3 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    5.  ( x, x )    ||" "\n" \
    "||    6.  ( x, x )    ||   2 ┠ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┨  ||    6.  ( x, x )    ||" "\n" \
    "||    7.  ( x, x )    ||   1 ┗ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┷ ┛  ||    7.  ( x, x )    ||" "\n" \
  "\\\\<===<===<===<===<===//     A B C D E F G H I J K L M N O  \\\\<===<===<===<===<===//"

#define GAME_PAGE_SCENE_RAW_TEXT_WIDTH       115
//#define GAME_PAGE_SCENE_RAW_TEXT_HEIGHT      16

#define DETACH_INDEX_COUNT_PER_ROW_OF_BOARD     17
#define DETACH_INDEX_COUNT_OF_BOARD_BOTTOM_ROW  16
#define DETACH_INDEX_COUNT_OF_GAME_INFORMATION  36

#ifdef WIN
#define charCountPerPieceIconStr    3
#define BLACK_TRIANGLE_ICON     "▲"
#define BLACK_CIRCLE_ICON       "●"
#define WHITE_TRIANGLE_ICON     "△"
#define WHITE_CIRCLE_ICON       "○"
#elif UNIX
#define charCountPerPieceIconStr    4
#define BLACK_TRIANGLE_ICON     "▲ "
#define BLACK_CIRCLE_ICON       "● "
#define WHITE_TRIANGLE_ICON     "△ "
#define WHITE_CIRCLE_ICON       "○ "
#endif

#define fillGamePageSceneDetachIndexes(indexes) do { \
    int k = -1; \
    indexes[++k] = 0; \
    for (int i = 0; i < BOARD_SIZE; ++i) { \
        indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 26; \
        if (i == 3) { \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 15; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 19; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 105; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 109; \
        } \
        else if (i == 5) { \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 16; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 20; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 106; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 110; \
        } \
        else if (8 <= i && i <= 14) { \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 12; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 16; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 102; \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 106; \
        } \
        for (int j = 0; j <= BOARD_SIZE; ++j) { \
            indexes[++k] = i * GAME_PAGE_SCENE_RAW_TEXT_WIDTH + 29 + j * charCountPerPieceIconStr; \
        } \
    } \
    for (int i = 0; i <= BOARD_SIZE; ++i) { \
        indexes[++k] = GAME_PAGE_SCENE_RAW_TEXT_WIDTH * 15 + 29 + i * 2; \
    } \
    indexes[++k] = strlen(GAME_PAGE_SCENE_RAW_TEXT); \
} while (0)

#define calculateExtraOffsetFromRowNumber(ROW_NUM) \
    (ROW_NUM <= 2 ? 0 : \
        (3 <= ROW_NUM && ROW_NUM <= 6 ? (ROW_NUM - 2) * 2 : \
            (ROW_NUM == 7 ? 8 : \
                (ROW_NUM == 8 ? 10 : \
                    (9 <= ROW_NUM && ROW_NUM <= 14 ? 10 + (ROW_NUM - 8) * 4 : \
                            0 \
    )   )   )   )   )

#define calculateCrossDotFragmentIndexFromBoardPoint(POINT) \
    2 + POINT.i * 17 + POINT.j + calculateExtraOffsetFromRowNumber(POINT.i)

#define calculateRowNumberFragmentIndex(ROW_NUM) \
    1 + ROW_NUM * 17 + calculateExtraOffsetFromRowNumber(ROW_NUM)

#define calculateColumnNumberFragmentIndex(COL_NUM) \
    292 + COL_NUM

#define getMoreMoveHistoryItemCount()     7

#define getBlackCurrentFragmentIndex()      52
#define getBlackLastStepFragmentIndex()     90
#define calculateBlackNearestNthMoveHistoryFragmentIndex(NTH) \
    NTH * 21 + 145
#define getWhiteCurrentFragmentIndex()      71
#define getWhiteLastStepFragmentIndex()     109
#define calculateWhiteNearestNthMoveHistoryFragmentIndex(NTH) \
    NTH * 21 + 164

#endif // GAME_PAGE_H
