#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "k.h"
#include "hof.h"
#include "ui.h"

int main()
{
    struct game game1 = {
        .board = {
            {'A', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', 'A'},
            {'B', ' ', ' ', ' '}},
        .score = 0};

    printf("is won: %d\n", is_game_won(game1));

    struct game game2 = {
        .board = {
            {'A', 'B', 'C', 'D'},
            {'E', 'F', 'G', 'H'},
            {'I', 'J', 'K', 'A'},
            {'B', 'C', 'D', 'E'}},
        .score = 0};

    printf("is move possible: %d\n", is_move_possible(game2));

    struct game game3 = {
        .board = {
            {'A', 'B', 'C', 'D'},
            {'A', 'B', 'C', 'D'},
            {'A', 'B', 'C', 'D'},
            {'A', 'B', 'C', 'D'}},
        .score = 1234};

    bool result = update(&game3, 0, -1);
    printf("%d\n", result);

    struct game game4;
    int i = 0;
    while (i < 4)
    {
        int j = 0;
        while (j < 4)
        {
            game4.board[i][j] = ' ';
            j++;
        }
        i++;
    }

    int ii = 0;
    while (ii < 10)
    {
        add_random_tile(&game4);
        ii++;
    }

    int iii = 0;
    while (iii < 4)
    {
        int j = 0;
        while (j < 4)
        {
            printf("%c ", game4.board[i][j]);
            j++;
        }
        printf("\n");
        iii++;
    }

    struct player players[100];
    int cislo = 10;
    bool success = save(players, cislo);
    if (success)
    {
        printf("Yes!\n");
    }
    else
    {
        printf("No.\n");
    }
}
