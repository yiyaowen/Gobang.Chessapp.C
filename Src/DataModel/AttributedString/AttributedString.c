#include "AttributedString.h"
#include "DataComparison.h"

#include <string.h>

char* getNewAttributeText(const char* sequences)
{
    Size sequencesLength = strlen(sequences);
    char* attributeText = (char*)malloc(sizeof(char)*(sequencesLength + 1));
    strcpy(attributeText, sequences);
    attributeText[sequencesLength] = '\0';
    return attributeText;
}

AttributedString* getNewAttributedString(const char* rawText)
{
    AttributedString* string = (AttributedString*)malloc(sizeof(AttributedString));
    string->rawTextLength = strlen(rawText);
    string->rawText = (char*)malloc(sizeof(char)*(string->rawTextLength + 1));
    strcpy(string->rawText, rawText);
    string->attributeTextLength = 2 * charCountPerAttributeSequence;
    string->attributeText = getNewAttributeText(DEFAULT_ATTR);
    string->prevString = string->nextString = NULL;
    return string;
}

Size getAttributedStringRawTextLength(AttributedString* string)
{
    Size length = string->rawTextLength;
    while ((string = string->nextString)) {
        length += string->rawTextLength;
    }
    return length;
}

Size getAttributedStringLength(AttributedString* string)
{
    Size length = string->rawTextLength + string->attributeTextLength + charCountPerAttributeSequence;
    while ((string = string->nextString)) {
        length += (string->rawTextLength + string->attributeTextLength + charCountPerAttributeSequence);
    }
    return length;
}

void normalizeAttributedString(AttributedString** string)
{
    char* normalRawText = copyAttributedStringRawText(*string);
    AttributedString* normalString = getNewAttributedString(normalRawText);
    releaseAttributedString(string);
    (*string) = normalString;
}

void detachNormalAttributedStringAtIndexes(AttributedString** string, int totalIndexCount, int* indexes)
{
    int firstIndex, secondIndex;
    int totalLength = getAttributedStringRawTextLength(*string);
    qsort(indexes, totalIndexCount, sizeof(int), intAscendingOrder);
    if (indexes[0] != 0 || indexes[totalIndexCount - 1] != totalLength) return;
    AttributedString** newStringList =
        (AttributedString**)malloc(sizeof(AttributedString*)*(totalIndexCount - 1));
    for (int i = 0; i < totalIndexCount - 1; ++i) {
        firstIndex = indexes[i];
        secondIndex = indexes[i + 1];
        char* newRawText = (char*)malloc(sizeof(char)*(secondIndex - firstIndex + 1));
        strncpy(newRawText, (*string)->rawText + firstIndex, secondIndex - firstIndex);
        newRawText[secondIndex - firstIndex] = '\0';
        AttributedString* newString = getNewAttributedString(newRawText);
        newStringList[i] = newString;
        free(newRawText);
    }
    for (int i = 0; i < totalIndexCount - 2; ++i) {
        newStringList[i]->nextString = newStringList[i + 1];
        newStringList[i + 1]->prevString = newStringList[i];
    }
    releaseAttributedString(string);
    (*string) = newStringList[0];
}

char* copyAttributedStringRawText(AttributedString* string)
{
    Size totalLength = getAttributedStringRawTextLength(string);
    char* normalRawText = (char*)malloc(sizeof(char)*(totalLength + 1));
    Size tmpLength = 0;
    while (string) {
        strcpy(normalRawText + tmpLength, string->rawText);
        tmpLength += string->rawTextLength;
        string = string->nextString;
    }
    return normalRawText;
}

char* copyAttributedStringText(AttributedString* string)
{
    Size totalLength = getAttributedStringLength(string);
    char* text = (char*)malloc(sizeof(char)*(totalLength + 1));
    Size tmpLength = 0;
    while (string) {
        strcpy(text + tmpLength, string->attributeText);
        tmpLength += string->attributeTextLength;
        strcpy(text + tmpLength, string->rawText);
        tmpLength += string->rawTextLength;
        strcpy(text + tmpLength, NONE_ATTR);
        tmpLength += charCountPerAttributeSequence;
        string = string->nextString;
    }
    return text;
}

void setAttributedStringNthFragmentNewRawText(AttributedString* string, int nth, const char* rawText)
{
    Size newLength = strlen(rawText);
    char* newRawText = (char*)malloc(sizeof(char)*(newLength + 1));
    strcpy(newRawText, rawText);
    while (nth-- > 0) string = string->nextString;
    string->rawTextLength = newLength;
    free(string->rawText);
    string->rawText = newRawText;
}

void setAttributedStringNthFragmentNewAttribute(AttributedString* string, int nth, const char* sequences)
{
    char* newAttributeText = getNewAttributeText(sequences);
    while (nth-- > 0) string = string->nextString;
    string->attributeTextLength = strlen(newAttributeText);
    free(string->attributeText);
    string->attributeText = newAttributeText;
}

void releaseAttributedString(AttributedString** string)
{
    if (!(*string)) return;
    free((*string)->rawText);
    free((*string)->attributeText);
    releaseAttributedString(&((*string)->nextString));
    (*string) = NULL;
}