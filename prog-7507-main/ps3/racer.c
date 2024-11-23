#include <stdio.h>

float calcul_k(int n, int t);

int main()
{
    int n, t;
    scanf("%d %d", &n, &t);
    float k = calcul_k(n, t);
    printf("%.6lf\n", k);
    return 0;
}

float calcul_k(int n, int t)
{
    float rychl = 0;
    float draha = 0;
    int i = 0;
    while (i < n)
    {
        int s, v;
        scanf("%d %d", &s, &v);
        rychl += v;
        draha += s;
        i++;
    }
    float k = (t / n) + (rychl / n) - (draha / t) ;
    return k;
}
