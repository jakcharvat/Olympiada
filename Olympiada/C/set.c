//
//  set.c
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#include "set.h"

struct Set;
struct SetPrivate {
    int *elements;
    int count;
    int size;
};


struct Set *createEmptySet() {
    struct Set *set = malloc(sizeof(struct Set));
    struct SetPrivate *p = malloc(sizeof(struct SetPrivate));
    
    p -> count = 0;
    p -> size = 0;
    p -> elements = NULL;
    set -> p = p;
    
    return set;
}


void addToSet(struct Set *set, int element) {
    int currentCount = set -> p -> count;
    int currentSize = set -> p -> size;
    int newElementSize = sizeof(element);
    int newSize = currentSize + newElementSize;
    
    int *newElements = realloc(set -> p -> elements, newSize);
    newElements[currentCount] = element;
    set -> p -> elements = newElements;
    set -> p -> count += 1;
    set -> p -> size = newSize;
}


bool isElementInSet(int element, struct Set *set) {
    for (int i = 0; i < set -> p -> count; i ++) {
        if (set -> p -> elements[i] == element) {
            return true;
        }
    }
    
    return false;
}
