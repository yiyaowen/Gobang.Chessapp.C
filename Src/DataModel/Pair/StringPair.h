#ifndef STRING_PAIR_H
#define STRING_PAIR_H

typedef struct type_StringPair {
    char* key;
    char* value;
} StringPair;

StringPair* getNewStringPair(const char* key, const char* value);

StringPair* splitStringToNewStringPairWithToken(const char* string, const char* token);

void releaseStringPair(StringPair** pair);

typedef struct type_StringPairList {
    int maxItemCount;
    int totalItemCount;
    StringPair** items;
} StringPairList;

StringPairList* getNewStringPairListWithCapacity(int capacity);

void appendStringPairToStringPairList(StringPair* pair, StringPairList* list);

char* getValueInStringPairListOfKey(const StringPairList* list, const char* key);

void releaseStringPairList(StringPairList** list);

#endif // STRING_PAIR_H