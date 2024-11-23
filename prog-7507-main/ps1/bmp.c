#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *reverse(const char *text){
    if (text == NULL)
        return NULL;

    int dlz = strlen(text);

    char *res = (char *)malloc(sizeof(char) * (dlz + 1));

    for (int i = dlz - 1, j = 0; i >= 0; i--, j++){
        res[j] = toupper(text[i]);
    }

    res[dlz] = '\0';

    return res;
}

char *vigenere_encrypt(const char *key, const char *text){
    if (key == NULL || text == NULL)
        return NULL;

    size_t strk = strlen(key);
    size_t strt = strlen(text);

    char *res = (char *)malloc(strt + 1);
    if (res == NULL)
        return NULL;

    size_t i = 0;
    size_t j = 0;

    while(i < strt){
        char g = text[i];
        if (isalpha(g)){
            int probel = toupper(key[j % strk]) - 'A';

            if (isupper(g)){
                res[i] = (g - 'A' + probel) % 26 + 'A';
            }
            else{
                res[i] = toupper((g - 'a' + probel) % 26 + 'a');
            }
            j++;
        }
        else{
            res[i] = g;
        }
        i++;
    }
    res[strt] = '\0';

    return res;
}

char *vigenere_decrypt(const char *key, const char *text)
{
    if (key == NULL || text == NULL)
        return NULL;

    size_t lklk = strlen(key);
    size_t ltlt = strlen(text);

    char *res = (char *)malloc(ltlt + 1);

    if (res == NULL)
        return NULL;
    
    size_t i = 0;
    size_t j = 0;

    while( i < ltlt){
        char b = text[i];

        if (isalpha(b)){
            int propusk = toupper(key[j % lklk]) - 'A';

            if (isupper(b)){
                res[i] = (b - 'A' - propusk + 26) % 26 + 'A';
            }
            else{
                res[i] = toupper((b - 'a' - propusk + 26) % 26 + 'a');
            }

            j++;
        }
        else{
            res[i] = b;
        }

        i++;
    }

    res[ltlt] = '\0';

    return res;
}

unsigned char *bit_encrypt(const char *text)
{
    if (text == NULL)
        return NULL;

    int tst = strlen(text);

    unsigned char *fin = (unsigned char *)malloc(sizeof(unsigned char) * tst + 1);

    fin[tst] = '\0';

    return fin;
}

char *bit_decrypt(const unsigned char *text)
{
    if (text == NULL)
        return NULL;

    int let = strlen((char *)text);

    char *rez = (char *)malloc(sizeof(char) * let + 1);

    rez[let] = '\0';

    return rez;
}

unsigned char *bmp_encrypt(const char *key, const char *text)
{
    if (key == NULL || text == NULL)
        return NULL;

    char *start;
    start = reverse(text);

    char *middle;
    middle = vigenere_encrypt(key, start);

    unsigned char *final;
    final = bit_encrypt(middle);

    free(start);
    free(middle);

    return final;
}

char *bmp_decrypt(const char *key, const unsigned char *text)
{
    if (key == NULL || text == NULL)
        return NULL;

    char *jeden;
    jeden = bit_decrypt(text);

    char *dva;
    dva = vigenere_decrypt(key, jeden);

    char *tri;
    tri = reverse(dva);

    free(jeden);
    free(dva);

    return tri;
}
