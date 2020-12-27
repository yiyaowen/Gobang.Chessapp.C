#ifndef SMART_DISPLAY_H
#define SMART_DISPLAY_H

#define clearScreen() do { \
    system("clear"); \
} while (0)

#define printWithDoubleBuffer(PRINT_PROCESS) do { \
    PRINT_PROCESS; \
} while (0)

#define clearAndPrintWithDoubleBuffer(DISPLAY_PROCESS) do { \
    clearScreen(); \
    DISPLAY_PROCESS; \
} while (0)

#endif // SMART_DISPLAY_H