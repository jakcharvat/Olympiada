//
//  krizovatky.c
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "krizovatky.h"

struct Krizovatka;
struct BFSKrizovatka;

struct Krizovatka *createKrizovatka(int id, int podVodou) {
    struct Krizovatka *krizovatka = malloc(sizeof(struct Krizovatka));
    krizovatka -> id = id;
    krizovatka -> podVodou = podVodou;
    krizovatka -> pripojeneKrizovatky = createEmptyVector();
    return krizovatka;
}


void spojitKrizovatky(struct Krizovatka *krizovatka1, struct Krizovatka *krizovatka2) {
    addToVector(krizovatka1 -> pripojeneKrizovatky, krizovatka2);
    addToVector(krizovatka2 -> pripojeneKrizovatky, krizovatka1);
}


void printKrizovatka(struct Krizovatka *krizovatka) {
    printf("\nKrizovatka %i %i:\nPripojene krizovatky - ", krizovatka -> id, krizovatka -> podVodou);
    printVector(krizovatka -> pripojeneKrizovatky);
    printf("---------\n");
}


void printKrizovatky(struct Krizovatka *krizovatky[], int n) {
    for (int i = 0; i < n; i ++) {
        printKrizovatka(krizovatky[n]);
    }
}
