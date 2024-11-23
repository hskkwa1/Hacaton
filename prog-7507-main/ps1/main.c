#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "playfair.h"

int main()
{
    char *obrat;
    obrat = reverse("Helho");
    printf("%s\n", obrat);

    char *negiv;
    negiv = vigenere_encrypt("CoMPuTeR", "Hello world!");
    printf("Result for function vigenere_encrypt() is: %s\n", negiv);

    char *degid;
    degid = vigenere_decrypt("CoMPuTeR", negiv);
    printf("Result for function vigenere_decrypt() is: %s\n", degid);

    unsigned char *bitty = bit_encrypt(negiv);
    char *botty = bit_decrypt(bitty);

    unsigned char *encbmp = bmp_encrypt("somekluce", "test for bmp is running");
    char *decbmp = bmp_decrypt("somekluce", encbmp);
    
    for (int i = 0; i < 38; i++){
        printf("%x ", encbmp[i]);
    }
    printf("\n");

    printf("%s\n", decbmp);
    for (int i = 0; i < 38; i++){
        printf("%c", decbmp[i]);
    }
    printf("\n");

    free(obrat);
    free(encbmp);
    free(decbmp);
    free(botty);
    free(bitty);
    free(negiv);
    free(degid);

    return 0;
}
