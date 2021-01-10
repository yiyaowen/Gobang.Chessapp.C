#ifndef CORE_RENJU_PATTERN_H
#define CORE_RENJU_PATTERN_H

typedef unsigned RenjuPattern;

#define SINGLE_PATTERN_SEAT_COUNT  5

#define RENJU_PATTERN_EMPTY 0

#define addNewPieceToRenjuPatternAtIndex(pattern, index) \
    ((pattern) |= (1 << (SINGLE_PATTERN_SEAT_COUNT - (index) - 1)))

#define addNewBanToRenjuPatternAtIndex(pattern, index) \
    addNewPieceToRenjuPatternAtIndex(pattern, index) 

#define removeOldBanFromRenjuPatternAtIndex(pattern, index) \
    ((pattern) &= (~(1 << (SINGLE_PATTERN_SEAT_COUNT - (index) - 1))))

#define isRenjuPatternOccupiedAtIndex(pattern, index) \
    ((pattern) & (1 << (SINGLE_PATTERN_SEAT_COUNT - (index) - 1)))

#define isRenjuPatternFilledWithPieces(pattern) \
    (getTotalPieceCountOfRenjuPattern((pattern)) == SINGLE_PATTERN_SEAT_COUNT)

#define copyRenjuPatternRemovePieceAtIndex(pattern, index) \
    ((pattern) & (~(1 << (SINGLE_PATTERN_SEAT_COUNT - (index) -1))))

int getTotalPieceCountOfRenjuPattern(RenjuPattern pattern);

// Three and Three ban
#define isRenjuPatternGroupLatentThreeAndThreeForm(indexToMove, blackPattern, whitePattern, banPattern) \
    ((whitePattern) == 0 && (banPattern) == 0 && ( \
    ((indexToMove) == 0 && ((blackPattern) == 10 || (blackPattern) == 6)) || \
    ((indexToMove) == 1 && ((blackPattern) == 5 || (blackPattern) == 18 || (blackPattern) == 3)) || \
    ((indexToMove) == 2 && ((blackPattern) == 9 || (blackPattern) == 18)) || \
    ((indexToMove) == 3 && ((blackPattern) == 24 || (blackPattern) == 9 || (blackPattern) == 20)) || \
    ((indexToMove) == 4 && ((blackPattern) == 10 || (blackPattern) == 12))))

#define isRenjuPatternGroupCertainThreeAndThreeForm(indexToMove, blackPattern, whitePattern, banPattern) \
    ((whitePattern) == 0 && (banPattern) == 0 && ( \
    ((indexToMove) == 1 && (blackPattern) == 6) || \
    ((indexToMove) == 2 && (blackPattern) == 10) || \
    ((indexToMove) == 3 && (blackPattern) == 12)))

// Four and Four ban
#define isRenjuPatternGroupCertainFourAndFourForm(indexToMove, blackPattern, whitePattern, banPattern) \
    ((whitePattern) == 0 && (banPattern) == 0 && (\
    ((indexToMove) == 0 && ((blackPattern) == 7 || (blackPattern) == 11 || (blackPattern) == 13 || (blackPattern) == 14)) || \
    ((indexToMove) == 1 && ((blackPattern) == 7 || (blackPattern) == 19 || (blackPattern) == 21 || (blackPattern) == 22)) || \
    ((indexToMove) == 2 && ((blackPattern) == 11 || (blackPattern) == 19 || (blackPattern) == 21 || (blackPattern) == 22)) || \
    ((indexToMove) == 3 && ((blackPattern) == 13 || (blackPattern) == 21 || (blackPattern) == 25 || (blackPattern) == 28)) || \
    ((indexToMove) == 4 && ((blackPattern) == 14 || (blackPattern) == 22 || (blackPattern) == 26 || (blackPattern) == 28))))

#define isRenjuPatternGroupParallelFourAndFourForm(indexToMove, blackPattern, whitePattern, banPattern) \
    (((indexToMove) == 1 || (indexToMove) == 3) && \
    (blackPattern) == 21 &&(whitePattern) == 0 && (banPattern) == 0)

//  Long Renju ban
#define isRenjuPatternGroupLatentLongRenjuForm(blackPattern, whitePattern, banPattern) \
    (getTotalPieceCountOfRenjuPattern(blackPattern) == 4 && (whitePattern) == 0 && (banPattern) == 0)

// Middle level
#define RENJU_PATTERN_BASE_SCORE            0
#define RENJU_PATTERN_INVALID_SCORE         0
#define RENJU_PATTERN_MIXED_SCORE           0
#define RENJU_PATTERN_EMPTY_SCORE           7
#define RENJU_PATTERN_FAVORS_SINGLE_SCORE   35
#define RENJU_PATTERN_ADVERSE_SINGLE_SCORE  15
#define RENJU_PATTERN_FAVORS_DOUBLE_SCORE   800
#define RENJU_PATTERN_ADVERSE_DOUBLE_SCORE  400
#define RENJU_PATTERN_FAVORS_TRIPLE_SCORE   15000
#define RENJU_PATTERN_ADVERSE_TRIPLE_SCORE  1800
#define RENJU_PATTERN_FAVORS_QUADRA_SCORE   800000
#define RENJU_PATTERN_ADVERSE_QUADRA_SCORE  100000

#define getFavorsScoreOfPieceCount(COUNT) \
    ((COUNT) == 1 ? RENJU_PATTERN_FAVORS_SINGLE_SCORE : \
    (COUNT) == 2 ? RENJU_PATTERN_FAVORS_DOUBLE_SCORE : \
    (COUNT) == 3 ? RENJU_PATTERN_FAVORS_TRIPLE_SCORE : \
    RENJU_PATTERN_FAVORS_QUADRA_SCORE)

#define getAdverseScoreOfPieceCount(COUNT) \
    ((COUNT) == 1 ? RENJU_PATTERN_ADVERSE_SINGLE_SCORE : \
    (COUNT) == 2 ? RENJU_PATTERN_ADVERSE_DOUBLE_SCORE : \
    (COUNT) == 3 ? RENJU_PATTERN_ADVERSE_TRIPLE_SCORE : \
    RENJU_PATTERN_ADVERSE_QUADRA_SCORE)

#endif // CORE_RENJU_PATTERN_H
