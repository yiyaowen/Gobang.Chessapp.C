#include "CorePointField.h"

#include <stdlib.h>

#define isPointInBoardSizeRange(POINT) \
	(0 <= (POINT).i && (POINT).i < CORE_BOARD_SIZE && 0 <= (POINT).j && (POINT).j < CORE_BOARD_SIZE)

CorePoint getCorePointFromPointFieldAlgorithm(RenjuGroupList* list)
{
	CoreScoreBoard pointFieldBoard;
	for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
		for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
			pointFieldBoard[i][j] = CORE_POINT_FIELD_BASE_SCORE;
		}
	}
	for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
		for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
			if (isCoreSideEmpty(list->gameBoard[i][j])) continue;
			CorePoint tmpPoint = { i, j };
			CorePointList* pointList = getNewEncapsulatedPointListOfPoint(tmpPoint);
			for (int k = 0; k < pointList->totalPointCount; ++k) {
				if (isPointInBoardSizeRange(pointList->points[k])) {
					if (!isCoreSideEmpty(list->gameBoard[pointList->points[k].i][pointList->points[k].j]))
						continue;
					pointFieldBoard[pointList->points[k].i][pointList->points[k].j]
						+= (list->favors == list->gameBoard[i][j] ?
							CORE_POINT_FIELD_FAVORS_SCORE : CORE_POINT_FIELD_ADVERSE_SCORE);
				}
			}
			releasePointList(&pointList);
		}
	}

	CorePoint point = { -1, -1 };
	int tmpMaxScore = 0;
	for (int i = 0; i < CORE_BOARD_SIZE; ++i) {
		for (int j = 0; j < CORE_BOARD_SIZE; ++j) {
			if ((isCoreSideWhite(list->favors) || isBanReasonEmpty(list->banBoard[i][j])) &&
				((pointFieldBoard[i][j] > tmpMaxScore) ||
				(pointFieldBoard[i][j] == tmpMaxScore &&
					(absInt(i - CORE_BOARD_SIZE / 2) + absInt(j - CORE_BOARD_SIZE / 2)) <
					(absInt(point.i - CORE_BOARD_SIZE / 2) + absInt(point.j - CORE_BOARD_SIZE / 2)))))
			{
				point.i = i; point.j = j;
				tmpMaxScore = pointFieldBoard[i][j];
			}
		}
	}

	return point;
}

CorePointList* getNewEncapsulatedPointListOfPoint(CorePoint point)
{
	CorePointList* list = (CorePointList*)coreNoNullMalloc(sizeof(CorePointList));
	list->totalPointCount = 8;
	list->points = (CorePoint*)coreNoNullMalloc(sizeof(CorePoint) * 8);
	list->points[0].i = list->points[1].i = list->points[2].i = point.i - 1;
	list->points[3].i = list->points[4].i = point.i;
	list->points[5].i = list->points[6].i =  list->points[7].i = point.i + 1;
	list->points[0].j = list->points[3].j = list->points[5].j = point.j - 1;
	list->points[1].j = list->points[6].j = point.j;
	list->points[2].j = list->points[4].j = list->points[7].j = point.j + 1;
	return list;
}