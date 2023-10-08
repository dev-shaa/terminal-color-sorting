#include <stdio.h>
#include "display.h"

inline void clear_screen()
{
    printf("\e[1;1H\e[2J");
}