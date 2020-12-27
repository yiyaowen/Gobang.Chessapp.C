#ifndef DATA_COMPARISON_H
#define DATA_COMPARISON_H

#define maxInt(a,b) (((a)>(b))?(a):(b))
#define minInt(a,b) (((a)<(b))?(a):(b))
#define maxDouble(a,b) maxInt(a,b)
#define minDouble(a,b) minInt(a,b)

int intAscendingOrder(const void* first, const void* second);

#endif // DATA_COMPARISON_H
