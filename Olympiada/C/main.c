//
//  main.c
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#include <stdio.h>
#include "krizovatky.h"
#include "vector.h"
#include "set.h"


int main() {
    int n, m, k;
    scanf("%i %i %i", &n, &m, &k);
    printf("%i - %i - %i", n, m, k);
    
    struct Krizovatka *krizovatky[n];
    for (int i = 0; i < n; i ++) {
        int podVodou;
        scanf("%i", &podVodou);
        
        struct Krizovatka *krizovatka = createKrizovatka(i, podVodou);
        krizovatky[i] = krizovatka;
    }
    
    for (int i = 0; i < m; i ++) {
        int krizovatka1, krizovatka2;
        scanf("%i %i", &krizovatka1, &krizovatka2);
        
        spojitKrizovatky(krizovatky[krizovatka1], krizovatky[krizovatka2]);
    }
    
    struct Vector *queue = createEmptyVector();
    addToVector(queue, krizovatky[n - 1]);
    struct Set *visitedPoints = createEmptySet();
    addToSet(visitedPoints, n - 1);
    
    while (queue -> count > 0) {
//        struct Krizovatka *current =
    }
    
routePrinting:
//    printf("\n%i\n", distance);
    
    return 0;
}
