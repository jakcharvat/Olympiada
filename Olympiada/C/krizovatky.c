//
//  krizovatky.c
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#include <stdio.h>
#include "krizovatky.h"

struct Krizovatka;

void testSize() {
    struct Krizovatka krizovatka;
    printf("%lu", sizeof(krizovatka));
}
