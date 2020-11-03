//
//  krizovatky.h
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#ifndef krizovatky_h
#define krizovatky_h

#include "vector.h"

struct Krizovatka {
    int id;
    int podVodou;
    struct Vector *pripojeneKrizovatky;
};


struct BFSKrizovatka {
    struct Krizovatka *krizovatka;
    int distance;
    struct Krizovatka *route;
};


struct Krizovatka *createKrizovatka(int id, int podVodou);
void spojitKrizovatky(struct Krizovatka *krizovatka1, struct Krizovatka *krizovatka2);
void printKrizovatka(struct Krizovatka *krizovatka);
void printKrizovatky(struct Krizovatka *krizovatky[], int n);


struct BFSKrizovatka *createBFSKrizovatka(struct Krizovatka *krizovatka, int distance, struct Krizovatka *route[distance]);

#endif /* krizovatky_h */
