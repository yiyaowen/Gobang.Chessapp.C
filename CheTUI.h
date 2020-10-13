#ifndef GOBANG_H
#define GOBANG_H

// 棋盘、棋子
#define SIZE 15
#define BLACKtem 10
#define WHITEtem 11
#define BLACK 20
#define WHITE 21

// 错误类型码
#define POS_VALID 0
#define OUT_OF_BOARD 1
#define OVERLAPPED 2
#define BAD_FORMAT 3

int Board[SIZE][SIZE];

char y;
int x;
int scanResult;

void InitBoardArray();              // 初始化空棋盘

void DisplayBoard();	            // 显示棋盘

void DisplayHint(int side);         // 显示提示语

void GetValidPosition(int side);    // 获取合法坐标输入

int IsPositionValid();              // 判断坐标是否合法

void DisplayErrorHint(int type);    // 显示错误提示语

void ClearInputBuffer();            // 清空输入缓冲区

#endif /* GOBANG_H */
