#ifndef DATA_COMPARISON_H
#define DATA_COMPARISON_H

#ifndef maxInt
#define maxInt(a,b) (((a)>(b))?(a):(b))
#endif

#ifndef minInt
#define minInt(a,b) (((a)<(b))?(a):(b))
#endif

int intAscendingOrder(const void* first, const void* second);

#endif // DATA_COMPARISON_H
