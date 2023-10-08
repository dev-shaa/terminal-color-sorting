#include "display.h"
#include <stdarg.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#endif

inline void clear_screen()
{
#ifdef _WIN32
    clrscr();
#else
    printf("\e[1;1H\e[2J");
#endif
}

void print_colored(const char *format, ...)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
#else
    printf(ANSI_COLOR_GREEN);
#endif

    va_list argptr;
    va_start(argptr, format); // Requires the last fixed parameter (to get the address)

    vprintf(format, argptr);

    va_end(argptr);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, saved_attributes);
#else
    printf(ANSI_COLOR_RESET);
#endif
}