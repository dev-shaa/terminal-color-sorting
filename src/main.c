#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "display.h"

char *colors[] = {
    ANSI_COLOR_RED,
    ANSI_COLOR_GREEN,
    ANSI_COLOR_YELLOW,
    ANSI_COLOR_BLUE,
    ANSI_COLOR_MAGENTA};

#define COLORS_COUNT 5
#define WIDTH COLORS_COUNT + 2
#define HEIGHT 4

int cells[WIDTH][HEIGHT];

/// @brief Called when starting the game.
void start();

/// @brief Repaints the screen.
void repaint();

/// @brief
void update();

/// @brief Checks if the game is resolved.
/// @return 1 if the game is resolved, 0 otherwise.
int is_resolved();

/// @brief Called when the game ends.
void destroy();

int main(int argc, char const *argv[])
{
    start();
    repaint();

    while (!is_resolved())
    {
        update();
        repaint();
    }

    destroy();

    return 0;
}

void start()
{
    // initialize random seed

    srand(time(NULL));

    // initialize all cells

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < COLORS_COUNT; j++)
            cells[j][i] = j;

        for (int j = COLORS_COUNT; j < WIDTH; j++)
            cells[j][i] = -1;
    }

    // shuffle cells with the Fisher–Yates shuffle algorithm
    // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = COLORS_COUNT - 1; j >= 1; j--)
        {
            int r = rand() % (j + 1);

            int temp = cells[j][i];
            cells[j][i] = cells[r][i];
            cells[r][i] = temp;
        }
    }
}

void repaint()
{
    clear_screen();

    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            char *cell = cells[j][i] == -1 ? EMPTY_CELL : OCCUPIED_CELL;
            char *color = cells[j][i] == -1 ? ANSI_COLOR_RESET : colors[cells[j][i]];
            printf(ANSI_COLOR_RESET "|%s%s" ANSI_COLOR_RESET "| ", color, cell);
        }

        printf("\n");
    }

    for (int j = 0; j < WIDTH; j++)
        printf(" ¯  ");

    printf("\n");

    for (int j = 0; j < WIDTH; j++)
        printf(" %d  ", j);

    printf("\n\n");
}

void update()
{
    int from, to;

    while (scanf("%d %d", &from, &to) != 2 || from < 0 || from >= WIDTH || to < 0 || to >= WIDTH || from == to)
    {
        printf("retry\n");
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        if (cells[from][i] == -1)
            continue;

        for (int j = HEIGHT - 1; j >= 0; j--)
        {
            if (cells[to][j] != -1)
                continue;

            cells[to][j] = cells[from][i];
            cells[from][i] = -1;
        }

        break;
    }
}

int is_resolved()
{
    for (int i = 0; i < WIDTH; i++)
    {
        int color = cells[i][0];

        for (int j = 1; j < HEIGHT; j++)
        {
            if (cells[i][j] != color)
                return 0;
        }
    }

    return 1;
}

void destroy()
{
    for (int i = 0; i < COLORS_COUNT; i++)
    {
        repaint();

        printf("%sCongratulations!!!\n\n", colors[i]);
        sleep(1);
    }
}
