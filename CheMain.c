#include "display.h"

extern int Board[SIZE][SIZE];

extern char y;
extern int x;
extern int scanResult;

int main()
{
	InitBoardArray();
	DisplayBoard();

    while (1)
    {
        // 黑子
        GetValidPosition(BLACK); 
        Board[SIZE-x][y-'A'] = BLACKtem;
        DisplayBoard();	
        Board[SIZE-x][y-'A'] = BLACK;

        // 白子
        GetValidPosition(WHITE);
        Board[SIZE-x][y-'A'] = WHITEtem;
        DisplayBoard();
        Board[SIZE-x][y-'A'] = WHITE;
    }

    return 0;
}
