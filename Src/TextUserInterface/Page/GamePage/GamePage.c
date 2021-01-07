#include "GamePage.h"
#include "Location/Location.h"
#include "DataUtility/DataConversion.h"
#include "SmartDisplay.h"
#include "TuiUtility.h"
#include "DataUtility/DataInteraction.h"
#include "Core.h"
#include "AudioPlayer.h"

#include <string.h>
#include <ctype.h>

GamePageSceneTUi* getNewGamePageSceneTui()
{
    GamePageSceneTUi* tui = (GamePageSceneTUi*)malloc(sizeof(GamePageSceneTUi));
    AttributedString* string = getNewAttributedString(GAME_PAGE_SCENE_RAW_TEXT);
    int detachIndexCount = BOARD_SIZE * DETACH_INDEX_COUNT_PER_ROW_OF_BOARD +
        DETACH_INDEX_COUNT_OF_BOARD_BOTTOM_ROW + DETACH_INDEX_COUNT_OF_GAME_INFORMATION + 2;
    int indexes[detachIndexCount];
    fillGamePageSceneDetachIndexes(indexes);
    detachNormalAttributedStringAtIndexes(&string, detachIndexCount, indexes);
    tui->string = string;
    return tui;
}

void changeHighlightedSelectedPointInGamePageSceneTui(Point currentPoint, Point lastPoint, GamePageSceneTUi* tui)
{
    int lastPointFragmentIndex = calculateCrossDotFragmentIndexFromBoardPoint(lastPoint);
    int lastRowNumberFragmentIndex = calculateRowNumberFragmentIndex(lastPoint.i);
    int lastColumnNumberFragmentIndex = calculateColumnNumberFragmentIndex(lastPoint.j); int pointFragmentIndex = calculateCrossDotFragmentIndexFromBoardPoint(currentPoint);
    int currentRowNumberFragmentIndex = calculateRowNumberFragmentIndex(currentPoint.i);
    int currentColumnNumberFragmentIndex = calculateColumnNumberFragmentIndex(currentPoint.j);

    if (!isPointNull(lastPoint)) {
        setAttributedStringNthFragmentNewAttribute(tui->string, lastPointFragmentIndex, DEFAULT_ATTR);
        setAttributedStringNthFragmentNewAttribute(tui->string, lastRowNumberFragmentIndex, DEFAULT_ATTR);
        setAttributedStringNthFragmentNewAttribute(tui->string, lastColumnNumberFragmentIndex, DEFAULT_ATTR);
    }
    if (!isPointNull(currentPoint)) {
        setAttributedStringNthFragmentNewAttribute(tui->string, pointFragmentIndex, RED_F_ATTR HIGHLIGHT_ATTR);
        setAttributedStringNthFragmentNewAttribute(tui->string, currentRowNumberFragmentIndex, RED_F_ATTR HIGHLIGHT_ATTR);
        setAttributedStringNthFragmentNewAttribute(tui->string, currentColumnNumberFragmentIndex, RED_F_ATTR HIGHLIGHT_ATTR);
    }
}

void drawNewPieceAtPointInGamePageSceneTui(Side whichSide, Point whichPoint, Point lastPoint, GamePageSceneTUi* tui)
{
    int pointFragmentIndex = calculateCrossDotFragmentIndexFromBoardPoint(whichPoint);
    int lastPointFragmentIndex = calculateCrossDotFragmentIndexFromBoardPoint(lastPoint);

    if (isBlackSide(whichSide)) {
        if (!isPointNull(whichPoint))
            setAttributedStringNthFragmentNewRawText(tui->string, pointFragmentIndex, BLACK_TRIANGLE_ICON);
        if (!isPointNull(lastPoint))
            setAttributedStringNthFragmentNewRawText(tui->string, lastPointFragmentIndex, WHITE_CIRCLE_ICON);
    }
    else {
        if (!isPointNull(whichPoint))
            setAttributedStringNthFragmentNewRawText(tui->string, pointFragmentIndex, WHITE_TRIANGLE_ICON);
        if (!isPointNull(lastPoint))
            setAttributedStringNthFragmentNewRawText(tui->string, lastPointFragmentIndex, BLACK_CIRCLE_ICON);
    }
}

#define fillLocationDescriptionFromPoint(DESC, LOCATION, POINT) do { \
    LOCATION = makeLocationFromPoint(POINT); \
    DESC = makeDescriptionStringFromLocation(LOCATION);         \
} while (0)
void updateGameInformationInGamePageSceneTui(GamePageData* data, GamePageSceneTUi* tui)
{
    Point point;
    Location location;
    int totalAvailableMoveCount;
    char* desc;
    Side currentSide = data->tmpData->currentActiveSide;

    if (isBlackSide(currentSide)) {
        point = data->tmpData->currentSelectedPoint;
        fillLocationDescriptionFromPoint(desc, location, point);
        setAttributedStringNthFragmentNewRawText(tui->string, getBlackCurrentFragmentIndex(), desc);
    }
    else {
        point = data->tmpData->currentSelectedPoint;
        fillLocationDescriptionFromPoint(desc, location, point);
        setAttributedStringNthFragmentNewRawText(tui->string, getWhiteCurrentFragmentIndex(), desc);
        free(desc);
    }

    if (!(data->tmpData->isLastMoveConfirmed)) return;

    point = getLastMovePointInGameRecordTable(data->recordTable);
    fillLocationDescriptionFromPoint(desc, location, point);

    if (isBlackSide(currentSide)) {
        setAttributedStringNthFragmentNewRawText(tui->string, getBlackLastStepFragmentIndex(), desc);
        free(desc);
        totalAvailableMoveCount = data->recordTable->totalMoveCount / 2 + data->recordTable->totalMoveCount % 2;
        for (int i = 0; i < minInt(totalAvailableMoveCount, getMoreMoveHistoryItemCount()); ++i) {
            point = getNearestNthMovePointOfSideInGameRecordTable(i, SIDE_BLACK, data->recordTable);
            fillLocationDescriptionFromPoint(desc, location, point);
            setAttributedStringNthFragmentNewRawText(tui->string, calculateBlackNearestNthMoveHistoryFragmentIndex(i), desc);
            free(desc);
        }
    }
    else {
        setAttributedStringNthFragmentNewRawText(tui->string, getWhiteLastStepFragmentIndex(), desc);
        free(desc);
        totalAvailableMoveCount = data->recordTable->totalMoveCount / 2;
        for (int i = 0; i < minInt(totalAvailableMoveCount, getMoreMoveHistoryItemCount()); ++i) {
            point = getNearestNthMovePointOfSideInGameRecordTable(i, SIDE_WHITE, data->recordTable);
            fillLocationDescriptionFromPoint(desc, location, point);
            setAttributedStringNthFragmentNewRawText(tui->string, calculateWhiteNearestNthMoveHistoryFragmentIndex(i), desc);
            free(desc);
        }
    }
}

void printGamePageSceneTui(GamePageSceneTUi* tui)
{
    char* tuiTextToPrint = copyAttributedStringText(tui->string);
    printf("%s", tuiTextToPrint);
    printf("\n\n");
    printf(PROMPT);
}

void releaseGamePageSceneTui(GamePageSceneTUi** tui)
{
    releaseAttributedString(&((*tui)->string));
    free(*tui);
    (*tui) = NULL;
}

#define DEFAULT_CORE_GAME_TAG   0

Page* getNewGamePage(GamePrefabConfig* prefabConfig)
{
    Page* game = getNewDefaultPage();
    game->id = getPageIdFromGameMode(prefabConfig->mode);
    game->name = getPageNameFromGameMode(prefabConfig->mode);
    game->desc = getPageDescFromGameMode(prefabConfig->mode);
    game->displayFunc = displayGamePage;
    game->updateFunc = updateGamePage;
    game->releaseFunc = releaseGamePage;

    GamePageData* rawData = (GamePageData*)malloc(sizeof(GamePageData));
    if (isGameModePvC(prefabConfig->mode)) {
        createNewCoreGameWithTag(DEFAULT_CORE_GAME_TAG, prefabConfig->machineSide);
    }
    rawData->prefabConfig = prefabConfig;
    rawData->recordTable = getNewGameRecordTable();
    rawData->tmpData = getNewGameTmpData();
    rawData->sceneTui = getNewGamePageSceneTui();
    game->data = getNewPageData();
    game->data->masterPageId = game->id;
    game->data->rawData = rawData;

    return game;
}

void printInputHint(Side side)
{
    if (isBlackSide(side)) {
        printf("Black " BLACK_CIRCLE_ICON "'s turn. ");
    }
    else {
        printf("White " WHITE_CIRCLE_ICON "'s turn. ");
    }
    printf("Please input the position, e.g. 'A4', 'b6'.\n");
    printf(PROMPT);
}

Point getValidMovePointFromUser(Route* route, GamePageData* data)
{
    char key;
    InputErrorType errorType;
    int validInputCount;
    Point point = data->tmpData->currentSelectedPoint;
    Location location = makeLocationFromPoint(point);

get_user_input:
    key = (char)getchar();
    if (isSpecialControlOption(key)) {
        clearInputBuffer();
        handleSpecialControlOption(key, route, data);
        data->tmpData->isLastMoveConfirmed = false;
        return point;
    }
    else if (key == '\n') {
        putCharBack(key);
        clearInputBuffer();
        if (getErrorTypeOfMovePoint(point, data) == INPUT_ERROR_TYPE_VALID) {
            data->tmpData->isLastMoveConfirmed = true;
            return point;
        }
        validInputCount = 1;
    }
    else {
        location.x = (char)toupper(key);
        validInputCount = scanf("%d", &(location.y));
        point = makePointFromLocation(location);
        clearInputBuffer();
    }

    if ((errorType = getErrorTypeOfMovePoint(point, data)) != INPUT_ERROR_TYPE_VALID || validInputCount != 1) {
        if (validInputCount != 1) {
            errorType = INPUT_ERROR_TYPE_BAD_FORMAT;
        }
        printWithDoubleBuffer(printInputErrorHint(errorType));
        point = data->tmpData->currentSelectedPoint;
        goto get_user_input;
    }

    data->tmpData->isLastMoveConfirmed = false;
    return point;
}

bool isSpecialControlOption(char key)
{
    if (key == 'q' || key == 'Q' ||
        key == 's' || key == 'S')
    {
        return true;
    }
    else {
        return false;
    }
}

void handleSpecialControlOption(char key, Route* route, GamePageData* data)
{
    switch (key)
    {
        // Quit
        case 'q':
        case 'Q':
        {
            route->status = ROUTE_OVER;
            route->exitStatus = ROUTE_EXIT_SUCCESS;
            return;
        }
        // Save
        case 's':
        case 'S':
        {
            char path[100];
            int validInputCount;

            printWithDoubleBuffer(
                    printf("Save game record to file. Please input target file path.\n");
                printf("File path: ");
            );
            validInputCount = scanf("%s", path);
            clearInputBuffer();
            if (validInputCount != 1) {
                printWithDoubleBuffer(
                    printf(HIGHLIGHT_TEXT(RED_TEXT("Can't read target file path."))
                        " Press enter to back to game. " HIGHLIGHT_TEXT("[Enter]"));
                );
                clearInputBuffer();
                return;
            }
            if (!exportGameRecordTableToFile(data->recordTable, path)) {
                printWithDoubleBuffer(
                    printf("Invalid target file path. Please make sure recursive directories exist.\n");
                    printf("Target file will be created if not exists. Try to check related permissions.\n");
                    printf(HIGHLIGHT_TEXT(RED_TEXT("Can't write target file."))
                           " Press enter to back to game." HIGHLIGHT_TEXT("[Enter]"));
                );
                clearInputBuffer();
                return;
            }
            printWithDoubleBuffer(
                printf("Target file %s saved successfully. Press enter to continue. "
                    HIGHLIGHT_TEXT("[Enter]"), path);
            );
            clearInputBuffer();
            return;
        }
        default:
            return;
    }
}

InputErrorType getErrorTypeOfMovePoint(Point point, GamePageData* data)
{
    if (point.i < 0 || point.i >= BOARD_SIZE ||
        point.j < 0 || point.j >= BOARD_SIZE)
    {
        return INPUT_ERROR_TYPE_OUT_OF_BOARD;
    }
    else if (data->tmpData->piecesGameBoard[point.i][point.j] != SIDE_EMPTY) {
        return INPUT_ERROR_TYPE_OVERLAPPED;
    }
    else {
        return INPUT_ERROR_TYPE_VALID;
    }
}

void printInputErrorHint(InputErrorType errorType)
{
    switch (errorType)
    {
        case INPUT_ERROR_TYPE_OUT_OF_BOARD:
        {
            printf("Position is out of the chessboard. Valid range: A~O & 1~15.\n");
            break;
        }
        case INPUT_ERROR_TYPE_OVERLAPPED:
        {
            printf("The position is occupied. Please choose another position.\n");
            break;
        }
        case INPUT_ERROR_TYPE_BAD_FORMAT:
        {
            printf("Bad position format. Please input a letter followed by a number.\n");
            break;
        }
        default:
        {
            printf("An unknown error occurred.\n");
            break;
        }
    }
    printf(PROMPT);
}

void displayGamePage(PageData* data)
{
    GamePageData* gameData = (GamePageData*)data->rawData;
    clearAndPrintWithDoubleBuffer(
        printGamePageSceneTui(gameData->sceneTui);
        printInputHint(gameData->tmpData->currentActiveSide);
    );
}

#define isMachineRound(CURRENT_SIDE, MACHINE_SIDE) ((CURRENT_SIDE) == (MACHINE_SIDE))

#define printGameOverHint(WINNER) do { \
    if (isBlackSide(WINNER)) \
        printf(RED_TEXT(HIGHLIGHT_TEXT("Black Win. "))); \
    else \
        printf(GREEN_TEXT(HIGHLIGHT_TEXT("White Win. "))); \
    printf("Press enter to continue. " HIGHLIGHT_TEXT("[Enter]")); \
    clearInputBuffer(); \
} while (0)

Route* updateGamePage(PageData* data, Route* routePassByGame)
{
    GamePageData* gameData = (GamePageData*)data->rawData;
    Side currentActiveSide = gameData->tmpData->currentActiveSide;
    Side machineSide = gameData->prefabConfig->machineSide;
    CorePrefabConfig prefabConfig;
    Point movePoint;

    if (!isEmptySide(gameData->tmpData->winner)) {
        printGameOverHint(gameData->tmpData->winner);
        routePassByGame->status = ROUTE_OVER;
        routePassByGame->exitStatus = ROUTE_EXIT_SUCCESS;
        return routePassByGame;
    }

    if (isMachineRound(currentActiveSide, machineSide))
        goto get_move_from_machine;
    else
        goto get_move_from_user;

get_move_from_user:
    movePoint = getValidMovePointFromUser(routePassByGame, gameData);
    playBeepSound();
    goto update_game_data;

get_move_from_machine:
    prefabConfig.side = getCorePrefabConfigSideFromGameSide(machineSide);
    prefabConfig.level = getCorePrefabConfigLevelFromGameLevel(gameData->prefabConfig->level);
    CorePoint corePoint = getCorePointFromCoreAlgorithm(&prefabConfig, DEFAULT_CORE_GAME_TAG);
    movePoint = makePoint(corePoint.i, corePoint.j);
    gameData->tmpData->isLastMoveConfirmed = true;
    goto update_game_data;

update_game_data:
    updateGamePageDataWithMovePoint(gameData, movePoint);

    return routePassByGame;
}

void updateGamePageDataWithMovePoint(GamePageData* data, Point movePoint)
{
    Side moveSide = data->tmpData->currentActiveSide;
    Point lastMovePoint = getLastMovePointInGameRecordTable(data->recordTable);
    Point lastSelectedPoint = data->tmpData->lastSelectedPoint;
    data->tmpData->lastSelectedPoint = movePoint;
    data->tmpData->currentSelectedPoint = movePoint;
    if (data->tmpData->isLastMoveConfirmed) {
        addNewMoveToGameTmpData(moveSide, movePoint, data->tmpData);
        addNewMoveToGameRecordTable(moveSide, movePoint, data->recordTable);
        addNewMovePieceToCoreGameWithTag(moveSide, makeCorePointFromPoint(movePoint), DEFAULT_CORE_GAME_TAG);
        changeHighlightedSelectedPointInGamePageSceneTui(movePoint, lastMovePoint, data->sceneTui);
        drawNewPieceAtPointInGamePageSceneTui(moveSide, movePoint, lastMovePoint, data->sceneTui);
        updateGameInformationInGamePageSceneTui(data, data->sceneTui);
        data->tmpData->isLastMoveConfirmed = false;
        reverseSide(data->tmpData->currentActiveSide);
        data->tmpData->winner = getWinnerSideInCoreGameWithTag(DEFAULT_CORE_GAME_TAG);
    }
    else {
        changeHighlightedSelectedPointInGamePageSceneTui(movePoint, lastSelectedPoint, data->sceneTui);
        updateGameInformationInGamePageSceneTui(data, data->sceneTui);
    }
}

void releaseGamePage(PageData** data)
{
    GamePageData* gameData = (GamePageData*)((*data)->rawData);
    if (isGameModePvC(gameData->prefabConfig->mode)) {
        removeCoreGameWithTag(DEFAULT_CORE_GAME_TAG);
    }
    releaseGamePrefabConfig(&(gameData->prefabConfig));
    releaseGameRecordTable(&(gameData->recordTable));
    releaseGameTmpData(&(gameData->tmpData));
    releaseGamePageSceneTui(&(gameData->sceneTui));
    free(gameData);
    free(*data);
    (*data) = NULL;
}