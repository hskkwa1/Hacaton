#include <string.h>
#include <stdio.h>

void function_mig_met(char *array)
{
    int l = strlen(array);

    int s = 0;

    int b = 0;

    while (b < l)
    {
        s += (array[b] - '0');
        b++;
    }

    sprintf(array, "%d", s);
}
int main()
{
    char array[100000];

    scanf("%s", array);

    do
    {
        function_mig_met(array);
    } while (strlen(array) > 1);

    printf("%s\n", array);
}
