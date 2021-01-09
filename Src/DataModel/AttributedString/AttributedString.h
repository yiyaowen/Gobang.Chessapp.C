#ifndef ATTRIBUTED_STRING_H
#define ATTRIBUTED_STRING_H

#include "ChessappDefinitions.h"

char* getNewAttributeText(const char* sequences);

typedef struct type_AttributedString {
    Size rawTextLength;
    char* rawText;
    Size attributeTextLength;
    char* attributeText;
    struct type_AttributedString* prevString;
    struct type_AttributedString* nextString;
} AttributedString;

AttributedString* getNewAttributedString(const char* rawText);

Size getAttributedStringRawTextLength(AttributedString* string);

Size getAttributedStringLength(AttributedString* string);

void normalizeAttributedString(AttributedString** string);

void detachNormalAttributedStringAtIndexes(AttributedString** string, int totalIndexCount, int* indexes);

char* copyAttributedStringRawText(AttributedString* string);

char* copyAttributedStringText(AttributedString* string);

void setAttributedStringNthFragmentNewRawText(AttributedString* string, int nth, const char* rawText);

void setAttributedStringNthFragmentNewAttribute(AttributedString* string, int nth, const char* sequences);

void releaseAttributedString(AttributedString** string);

#endif // ATTRIBUTED_STRING_H