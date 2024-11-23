#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Uzel
{
    int znam;

    struct Uzel *l;

    struct Uzel *p;
};

struct Uzel *New(int znam)
{
    struct Uzel *NewUzel = (struct Uzel *)malloc(sizeof(struct Uzel));

    NewUzel->znam = znam;

    NewUzel->l = NULL;

    NewUzel->p = NULL;
    
    return NewUzel;
}

struct Uzel *Paste(struct Uzel *res, int znam)
{
    if (res == NULL)
    {
        return New(znam);
    }

    if (znam < res->znam)
    {
        res->l = Paste(res->l, znam);
    }
    else
    {
        res->p = Paste(res->p, znam);
    }

    return res;
}

int Cmpr(struct Uzel *res1, struct Uzel *res02)
{
    if (res1 == NULL && res02 == NULL)
    {
        return 1;
    }

    if (res1 == NULL || res02 == NULL)
    {
        return 0;
    }

    int OnRight = Cmpr(res1->p, res02->p);

    int OnLeft = Cmpr(res1->l, res02->l);

    return OnLeft && OnRight;
}

int Plus(int vsetko[][20], int n, int k)
{
    int Stromy = 0;

    int i = 0;

    struct Uzel *res[n];

    while (i < n)
    {
        res[i] = NULL;

        int o = 0;

        while (o < k)
        {
            res[i] = Paste(res[i], vsetko[i][o]);

            o++;
        }

        int Rare = 1;

        int j = 0;

        while (j < i)
        {
            if (Cmpr(res[i], res[j]))
            {
                Rare = 0;

                break;
            }
            
            j++;
        }

        if (Rare)
        {
            Stromy++;
        }

        i++;
    }

    return Stromy;
}

int main()
{
    int n, k;

    scanf("%d %d", &n, &k);

    int vsetko[n][20];

    int i = 0;

    while (i < n)
    {
        int j = 0;

        while (j < k)
        {
            scanf("%d", &vsetko[i][j]);

            j++;
        }

        i++;
    }

    int Stromy = Plus(vsetko, n, k);

    printf("%d\n", Stromy);
}


