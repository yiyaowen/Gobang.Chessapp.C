#include "StringPair.h"
#include "ChessappDefinitions.h"

#include <stdlib.h>
#include <string.h>

StringPair* getNewStringPair(const char* key, const char* value)
{
    StringPair* pair = (StringPair*)malloc(sizeof(StringPair));
    pair->key = (char*)malloc(sizeof(char)*(strlen(key) + 1));
    pair->value = (char*)malloc(sizeof(char)*(strlen(value) + 1));
    strcpy(pair->key, key);
    strcpy(pair->value, value);
    return pair;
}

StringPair* splitStringToNewStringPairWithToken(const char* string, const char* token)
{
    Size stringLength = strlen(string);
    Size tokenLength = strlen(token);
    if (stringLength < tokenLength) return NULL;
    for (int i = 0; i <= (stringLength - tokenLength); ++i) {
        if (strncmp(string + i, token, tokenLength) == 0) {
            char* key = (char*)malloc(sizeof(char)*(i + 1));
            char* value = (char*)malloc(sizeof(char)*(stringLength - tokenLength - i + 1));
            strncpy(key, string, i); key[i] = '\0';
            strcpy(value, string + i + tokenLength);
            StringPair* pair = getNewStringPair(key, value);
            free(key);
            free(value);
            return pair;
        }
    }
    return NULL;
}

void releaseStringPair(StringPair** pair)
{
    free((*pair)->key);
    free((*pair)->value);
    free(*pair);
    *pair = NULL;
}

StringPairList* getNewStringPairListWithCapacity(int capacity)
{
    StringPairList* list = (StringPairList*)malloc(sizeof(StringPairList));
    list->maxItemCount = capacity;
    list->totalItemCount = 0;
    list->items = (StringPair**)malloc(sizeof(StringPair*)*capacity);
    for (int i = 0; i < capacity; ++i) list->items[i] = NULL;
    return list;
}

void appendStringPairToStringPairList(StringPair* pair, StringPairList* list)
{
    if (list->totalItemCount < list->maxItemCount)
        list->items[list->totalItemCount++] = pair;
}

char* getValueInStringPairListOfKey(const StringPairList* list, const char* key)
{
    for (int i = 0; i < list->totalItemCount; ++i) {
        if (strcmp(list->items[i]->key, key) == 0) {
            return list->items[i]->value;
        }
    }
    return NULL;
}

void releaseStringPairList(StringPairList** list)
{
    for (int i = 0; i < (*list)->totalItemCount; ++i) {
        releaseStringPair((*list)->items + i);
    }
    free((*list)->items);
    free(*list);
    *list = NULL;
}