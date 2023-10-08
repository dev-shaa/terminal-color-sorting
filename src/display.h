#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef _WIN32

#include <WinCon.h>

#define ANSI_COLOR_RED FOREGROUND_RED
#define ANSI_COLOR_BLUE FOREGROUND_BLUE
#define ANSI_COLOR_GREEN FOREGROUND_GREEN
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"

#else

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#endif

#define EMPTY_CELL " "
#define OCCUPIED_CELL "●"

/// @brief Clears the terminal screen.
void clear_screen();

void print_colored(const char *format, ...);

#endif