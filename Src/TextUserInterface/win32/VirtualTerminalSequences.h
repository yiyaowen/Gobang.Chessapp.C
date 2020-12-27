#ifndef VIRTUAL_TERMINAL_SEQUENCES_H
#define VIRTUAL_TERMINAL_SEQUENCES_H

#define printVTSErrorMessage() do { \
    printf("Can't enable Virtual Terminal Sequences on your Windows.\n"); \
    printf("Please make sure you are using the new cmd.exe.\n"); \
} while (0)

#define enableVirtualTerminalSequences() do { \
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); \
    if (hStdOut == INVALID_HANDLE_VALUE) { \
        printVTSErrorMessage(); \
        printf("Error - GetStdHandle(STD_OUTPUT_HANDLE);\n"); \
        exit(EXIT_FAILURE); \
    } \
    DWORD dwMode = 0; \
    if (!GetConsoleMode(hStdOut, &dwMode)) { \
        printVTSErrorMessage(); \
        printf("Error - GetConsoleMode(hOut, &dwMode);\n"); \
        exit(EXIT_FAILURE); \
    } \
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; \
    if (!SetConsoleMode(hStdOut, dwMode)) { \
        printVTSErrorMessage(); \
        printf("Error - SetConsoleMode(hOut, dwMode);\n"); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#endif // VIRTUAL_TERMINAL_SEQUENCES_H