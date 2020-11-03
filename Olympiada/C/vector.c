//
//  vector.c
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


struct Vector;
struct VectorPrivate {
    int size;
};


struct Vector *createEmptyVector() {
    struct Vector *vector = malloc(sizeof(struct Vector));
    vector -> krizovatky = NULL;
    vector -> count = 0;
    
    struct VectorPrivate *p = malloc(sizeof(struct VectorPrivate));
    p -> size = 0;
    vector -> p = p;
    return vector;
}


void addToVector(struct Vector *vector, struct Krizovatka *krizovatka) {
    int currentCount = vector -> count;
    int currentSize = vector -> p -> size;
    int newKrizovatkaSize = sizeof(krizovatka);
    int newSize = currentSize + newKrizovatkaSize;
    
    struct Krizovatka* *reallocated = realloc(vector -> krizovatky, newSize);
    reallocated[currentCount] = krizovatka;
    vector -> krizovatky = reallocated;
    
    vector -> count = currentCount + 1;
    vector -> p -> size = newSize;
}


struct Krizovatka *removeFirstFromVector(struct Vector *vector) {
    if (vector -> count <= 0) {
        printf("No elements in vector");
        return NULL;
    }
    
    struct Krizovatka *first = vector -> krizovatky[0];         // Get first element
    for (int i = 1; i < vector -> count; i ++) {
        vector -> krizovatky[i - 1] = vector -> krizovatky[i];  // Shift every other element
    }
    vector -> krizovatky[vector -> count - 1] = NULL;
    
    int currentSize = vector -> p -> size;
    int newSize = currentSize - (int) sizeof(first);
    struct Krizovatka* *reallocated = realloc(vector -> krizovatky, newSize);
    
    vector -> krizovatky = reallocated;
    vector -> count -= 1;
    vector -> p -> size = newSize;
    
    return first;
}


void printVector(struct Vector *vector) {
    printf("Vector of size %i:\n", vector -> count);
    
    for (int i = 0; i < vector -> count; i++) {
        printf("Krizovatka s id: %i\n", vector -> krizovatky[i] -> id);
    }
    
    printf("---------\n");
}
