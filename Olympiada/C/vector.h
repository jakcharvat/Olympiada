//
//  vector.h
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#ifndef vector_h
#define vector_h

#include "krizovatky.h"

struct Vector {
    struct Krizovatka* *krizovatky;
    int count;
    struct VectorPrivate *p;
};


struct Vector *createEmptyVector(void);
void addToVector(struct Vector *vector, struct Krizovatka *krizovatka);
struct Krizovatka *removeFirstFromVector(struct Vector *vector);
void printVector(struct Vector *vector);

#endif /* vector_h */
