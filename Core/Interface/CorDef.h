#ifndef INCLUDE_CORE_DEF_H
#define INCLUDE_CORE_DEF_H

#define COR_BOARD_SIZE  15

typedef int COR_DEFAULT_FLAT_BOARD[COR_BOARD_SIZE][COR_BOARD_SIZE];

typedef int COR_GAME_RECORD_BOARD[COR_BOARD_SIZE][COR_BOARD_SIZE];

typedef struct {
    int x;
    char y;
} COR_DEFAULT_FLAT_POSITION, COR_POSITION;

typedef struct {
    int i;
    int j;
} COR_DEFAULT_ARRAY_POSITION, COR_INDEXER;

typedef struct {
    int side;
    int level;
} ANALYSIS_PREFAB_CONFIG;

#define APC_NULL    2002

/* iSide */
#define APC_SIDE_BLACK  -1
#define APC_SIDE_WHITE   1

/* iLevel */
#define APC_LEVEL_DRUNK         -100

#define APC_LEVEL_LOW       0
#define APC_LEVEL_MIDDLE    1
#define APC_LEVEL_HIGH      2

#define APC_LEVEL_INVINCIBLE    100

#define APC_LEVEL_RANDOM    42

#endif /* INCLUDE_CORE_DEF_H */
