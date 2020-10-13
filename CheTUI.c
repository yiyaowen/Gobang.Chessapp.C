#include <stdio.h> 
#include <stdlib.h>

#include "display.h"

extern int Board[SIZE][SIZE];

extern char y;
extern int x;
extern int scanResult;

// 初始化空棋盘
void InitBoardArray()
{
	int j, i; 
	
	Board[0][0] = 1;
	Board[0][SIZE - 1] = 2;
	Board[SIZE - 1][SIZE - 1] = 3;
	Board[SIZE - 1][0] = 4;
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][0] = 5;
	}
	
	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[0][i] = 6;
	}
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][SIZE - 1] = 7;
	}
	
	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[SIZE - 1][i] = 8;
	}
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		for (i = 1; i <= SIZE - 2; i++)
		{
			Board[j][i] = 9;
		}
	}
}

// 显示棋盘
void DisplayBoard() 
{	
	int i, j;
	char line;
	char ary;
	
#ifdef WIN
	system("cls");
#elif UNIX
    system("clear");
#else
    // 默认清屏 
    system("cls");      
#endif

	for(j = 0,line = 15; j <= SIZE - 1; j++)
	{
		printf("%2d",line);
		line -= 1;
		for(i = 0; i <= SIZE - 1; i++)
		{
			switch(Board[j][i])
			{
			case 1:
				printf("┏");
				break;
				
			case 2:
				printf("┓");
				break;
				
			case 3:
				printf("┛");
				break;
				
			case 4:
				printf("┗");
				break;
				
			case 5:
				printf("┠");
				break;
				
			case 6:
				printf("┯");
				break;
				
			case 7:
				printf("┨");
				break;
				
			case 8:
				printf("┷");
				break;
				
			case 9:
				printf("┼");
				break;
				
            // 黑子上一步
			case BLACKtem:      
				printf("▲");
				break;
				
            // 白子上一步
			case WHITEtem:      
				printf("△");
				break;
				
            // 黑子通常
			case BLACK:      
				printf("●");
				break;
            
            // 白子通常
			case WHITE:
				printf("○");
				break;
			}
			if(i == SIZE - 1)
			{
				printf("\n");
			}
			
		}
	}
	
	printf("   ");
	for (ary = 'A'; ary < 'A' + SIZE ; ary++)
		printf("%c ",ary);
	
	printf("\n");
}

// 显示提示语
void DisplayHint(int side)
{
    if (side == BLACK)
        printf("黑棋● 的回合. ");
    else if (side == WHITE)
        printf("白棋○ 的回合. ");
    printf("请输入棋子的坐标, 例如: 'A4'.\n");
    printf("坐标: ");
}

// 获取合法坐标输入
void GetValidPosition(int side)
{
    // 提示输入
    DisplayHint(side);
    // 获得屏幕输入的坐标
    scanResult = scanf("%c%d",&y,&x);
    ClearInputBuffer();

    // 如果两个必要条件之一不满足, 则提示重新输入
    // 1. 获取字符成功、格式正确
    // 2. 坐标在棋盘界内、没有重叠
    while (1) {

        // 获取错误类型
        int errorType;
        if (scanResult != 2) {
            errorType = BAD_FORMAT;
        }
        else {
            errorType = IsPositionValid();
        }

        // 判断是否有错误需要处理
        if (errorType != POS_VALID) {
            // 提示错误输入
            DisplayErrorHint(errorType);
            // 获得屏幕输入的坐标
            scanResult = scanf("%c%d",&y,&x); 
            ClearInputBuffer();
        }
        else {
            break;
        }
    }
}

// 判断坐标是否合法
int IsPositionValid()
{
    if (!('A' <= (y &= 0x5f)  && y <= 'O' && 1 <= x && x <= 15)) {
        return OUT_OF_BOARD;
    }
    else if (Board[SIZE-x][y-'A'] == BLACK ||
             Board[SIZE-x][y-'A'] == BLACKtem ||
             Board[SIZE-x][y-'A'] == WHITE ||
             Board[SIZE-x][y-'A'] == WHITEtem) {
        return OVERLAPPED;
    } 
    else {
        return POS_VALID;
    }
}
    
// 显示错误提示语
void DisplayErrorHint(int type)
{
    switch (type)
    {
    case OUT_OF_BOARD:
        printf("坐标超出棋盘边界. 合法的坐标: A~O 和 1~15\n");
        break;

    case OVERLAPPED:
        printf("该位置已有棋子. 请选择空位置落子.\n");
        break;

    case BAD_FORMAT:
        printf("坐标格式错误. 请先输入一个字母，紧接着再输入一个数字.\n");
        break;

    default:
        printf("发生未知类型的错误.\n");
        break;
    }
    printf("坐标: ");
}

// 清空输入缓冲区
void ClearInputBuffer()
{
    while (getchar() != '\n')
        ;
}
