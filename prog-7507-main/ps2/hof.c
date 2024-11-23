#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct player
{
    char name[50];
    int score;
};

bool save(struct player list[], int size)
{
    FILE *fp;
    fp = fopen("HOF_FILE", "w");
    if (fp == NULL)
        return false;
    int i = 0;
    while (i < size)
    {
        fprintf(fp, "%s %d\n", list[i].name, list[i].score);
        i++;
    }
    fclose(fp);
    return true;
}
