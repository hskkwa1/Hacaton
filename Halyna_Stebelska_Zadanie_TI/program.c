#include <stdio.h>
#include <stdlib.h>

int **graf;
int POCET_VRCHOL;

int najdiStartovaciVrchol() {
    int pocetNeparnych = 0;
    int startovaciVrchol = 0; // Predvolený štartovací vrchol
    for (int i = 0; i < POCET_VRCHOL; i++) {
        int stupen = 0;
        for (int j = 0; j < POCET_VRCHOL; j++) {
            if (graf[i][j])
                stupen++;
        }
        if (stupen % 2 != 0) {
            pocetNeparnych++;
            startovaciVrchol = i; // Nastav štartovací vrchol na jeden z vrcholov s neparným stupňom
        }
    }
    if (pocetNeparnych == 0) {
        printf("Graf má Eulerov okruh.\n");
        return 0; // Štartuj na vrchole 0, ak existuje Eulerov okruh
    } else if (pocetNeparnych == 2) {
        printf("Graf má Eulerovu cestu.\n");
        return startovaciVrchol; // Štartuj na jednom z vrcholov s neparným stupňom
    } else {
        printf("Graf nemá ani Eulerovu cestu, ani okruh.\n");
        exit(0); // Ukonči, ak neexistuje Eulerova cesta ani okruh
    }
}

void dfsPomocna(int v, int navstivene[]) {
    navstivene[v] = 1;
    for (int i = 0; i < POCET_VRCHOL; i++) {
        if (graf[v][i] && !navstivene[i])
            dfsPomocna(i, navstivene);
    }
}

int jeSpojity() {
    int navstivene[POCET_VRCHOL];
    int startovaciVrchol = -1;

    for (int i = 0; i < POCET_VRCHOL; i++) {
        navstivene[i] = 0;
        for (int j = 0; j < POCET_VRCHOL; j++) {
            if (graf[i][j]) {
                startovaciVrchol = i;
                break;
            }
        }
        if (startovaciVrchol != -1) break;
    }

    if (startovaciVrchol == -1)
        return 1; // Považuj za spojitý, ak neexistujú hrany

    dfsPomocna(startovaciVrchol, navstivene);

    for (int i = 0; i < POCET_VRCHOL; i++) {
        for (int j = 0; j < POCET_VRCHOL; j++) {
            if (graf[i][j] && !navstivene[i])
                return 0;
        }
    }
    return 1;
}

void fleuryhoAlgoritmus(int start) {
    for (int v = 0; v < POCET_VRCHOL; v++) {
        if (graf[start][v]) {
            printf("%d--%d ", start, v);
            graf[start][v] = graf[v][start] = 0; // Odstráň hranu
            fleuryhoAlgoritmus(v);
            return;
        }
    }
}

void uvolniGraf() {
    for (int i = 0; i < POCET_VRCHOL; i++) {
        free(graf[i]);
    }
    free(graf);
}

int main() {
    printf("Zadajte počet vrcholov: ");
    scanf("%d", &POCET_VRCHOL);

    if (POCET_VRCHOL <= 0) {
        printf("Neplatný počet vrcholov.\n");
        return 1;
    }

    graf = (int **)malloc(POCET_VRCHOL * sizeof(int *));
    for (int i = 0; i < POCET_VRCHOL; i++) {
        graf[i] = (int *)malloc(POCET_VRCHOL * sizeof(int));
        if (graf[i] == NULL) {
            printf("Alokácia pamäte zlyhala!\n");
            for (int j = 0; j < i; j++) {
                free(graf[j]);
            }
            free(graf);
            return 1;
        }
    }

    printf("Zadajte maticu susednosti:\n");
    for (int i = 0; i < POCET_VRCHOL; i++) {
        for (int j = 0; j < POCET_VRCHOL; j++) {
            scanf("%d", &graf[i][j]);
        }
    }

    int startovaciVrchol = najdiStartovaciVrchol();
    printf("Štartovací vrchol pre Eulerovu cestu/okruh: %d\n", startovaciVrchol);
    fleuryhoAlgoritmus(startovaciVrchol);
    printf("\n");

    uvolniGraf();
    return 0;
}
