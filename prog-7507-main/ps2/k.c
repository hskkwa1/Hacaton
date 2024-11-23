#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "k.h"

int atodva(char letter)
{
    switch (letter)
    {
    case 'A':
        return 2;
    case 'B':
        return 4;
    case 'C':
        return 8;
    case 'D':
        return 16;
    case 'E':
        return 32;
    case 'F':
        return 64;
    case 'G':
        return 128;
    case 'H':
        return 256;
    case 'I':
        return 512;
    case 'J':
        return 1024;
    default:
        return 0;
    }
}

bool is_game_won(const struct game game)
{
    int i = 0;
    while (i < SIZE)
    {
        int j = 0;
        while (j < SIZE)
        {
            if (game.board[i][j] == 'K')
            {
                return true;
            }
            j++;
        }
        i++;
    }
    return false;
}

bool is_move_possible(const struct game game)
{
    int i, j;

    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            if (game.board[i][j] == ' ')
            {
                return true;
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE - 1)
        {
            if (game.board[i][j] == game.board[i][j + 1])
            {
                return true;
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < SIZE - 1)
    {
        j = 0;
        while (j < SIZE)
        {
            if (game.board[i][j] == game.board[i + 1][j])
            {
                return true;
            }
            j++;
        }
        i++;
    }

    return false;
}

bool update(struct game *game, int dy, int dx)
{
    if ((dy != 0 && dx != 0) || (dy == 0 && dx == 0))
        return false;
    int g, m, w;
    bool go = false;
    if (dy == -1)
    {
        m = 0;
        while (m < SIZE)
        {
            g = 1;
            while (g < SIZE)
            {
                if (game->board[g][m] == ' ')
                {
                    g++;
                    continue;
                }
                w = g;
                while (w > 0)
                {
                    if (game->board[w - 1][m] == ' ')
                    {
                        game->board[w - 1][m] = game->board[w][m];
                        game->board[w][m] = ' ';
                        go = true;
                    }
                    else if (game->board[w - 1][m] == game->board[w][m])
                    {
                        int value = atodva(game->board[w][m]) * 2;
                        game->score += value;
                        game->board[w - 1][m]++;
                        game->board[w][m] = ' ';
                        go = true;
                        break;
                    }
                    else
                    {
                        break;
                    }
                    w--;
                }
                g++;
            }
            m++;
        }
    }
    else if (dy == 1)
    {
        m = 0;
        while (m < SIZE)
        {
            g = SIZE - 2;
            while (g >= 0)
            {
                if (game->board[g][m] == ' ')
                {
                    g--;
                    continue;
                }

                w = g;
                while (w < SIZE - 1)
                {
                    if (game->board[w + 1][m] == ' ')
                    {
                        game->board[w + 1][m] = game->board[w][m];
                        game->board[w][m] = ' ';
                        go = true;
                    }
                    else if (game->board[w + 1][m] == game->board[w][m])
                    {
                        int value = atodva(game->board[w][m]) * 2;
                        game->score += value;
                        game->board[w + 1][m]++;
                        game->board[w][m] = ' ';
                        go = true;
                        break;
                    }
                    else
                    {
                        break;
                    }

                    w++;
                }

                g--;
            }

            m++;
        }
    }
    else if (dx == 1)
    {
        g = 0;
        while (g < SIZE)
        {
            m = SIZE - 2;
            while (m >= 0)
            {
                if (game->board[g][m] == ' ')
                {
                    m--;
                    continue;
                }
                w = m;
                while (w < SIZE - 1)
                {
                    if (game->board[g][w + 1] == ' ')
                    {
                        game->board[g][w + 1] = game->board[g][w];
                        game->board[g][w] = ' ';
                        go = true;
                    }
                    else if (game->board[g][w + 1] == game->board[g][w])
                    {
                        int value = atodva(game->board[g][w]) * 2;
                        game->score += value;
                        game->board[g][w + 1]++;
                        game->board[g][w] = ' ';
                        go = true;
                        break;
                    }
                    else
                    {
                        break;
                    }
                    w++;
                }
                m--;
            }
            g++;
        }
    }
    else if (dx == -1)
    {
        g = 0;
        while (g < SIZE)
        {
            m = 1;
            while (m < SIZE)
            {
                if (game->board[g][m] == ' ')
                {
                    m++;
                    continue;
                }
                w = m;
                while (w > 0)
                {
                    if (game->board[g][w - 1] == ' ')
                    {
                        game->board[g][w - 1] = game->board[g][w];
                        game->board[g][w] = ' ';
                        go = true;
                    }
                    else if (game->board[g][w - 1] == game->board[g][w])
                    {
                        int value = atodva(game->board[g][w]) * 2;
                        game->score += value;
                        game->board[g][w - 1]++;
                        game->board[g][w] = ' ';
                        go = true;
                        break;
                    }
                    else
                    {
                        break;
                    }
                    w--;
                }
                m++;
            }
            g++;
        }
    }
    return go;
}

void add_random_tile(struct game *game)
{
    int row, col;
    // find random, but empty tile
    do
    {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if (rand() % 2 == 0)
    {
        game->board[row][col] = 'A';
    }
    else
    {
        game->board[row][col] = 'B';
    }
}
