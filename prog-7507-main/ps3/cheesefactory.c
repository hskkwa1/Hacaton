#include <stdio.h>

float M3(float h);

float calcul_wide(int M, int S);

#define PI 3.14159265358979323846

int main()
{
    int M, S;

    scanf("%d %d", &M, &S);

    int j = 0;

    float wide = calcul_wide(M, S);

    while (j < S)
    {
        printf("%.6lf\n", wide);
        j++;
    }

    return 0;
}

float calcul_wide(int M, int S)
{
    float wide = 100.0 / S;

    int j = 0;

    while (j < M)
    {
        int R, x, y, z;

        scanf("%d %d %d %d", &R, &x, &y, &z);

        float h = (2.0 - y + R * x) / 1000.0;

        wide = M3(h);

        j++;
    }

    return wide;
}

float M3(float h)
{
    return PI * (h - 3.0*h + (1.0 - h) / h - 2.0);
}
