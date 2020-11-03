//
//  set.h
//  Olympiada
//
//  Created by Jakub Charvat on 02.11.2020.
//

#ifndef set_h
#define set_h

#include <stdlib.h>
#include <stdbool.h>

struct Set {
    struct SetPrivate *p;
};


struct Set *createEmptySet(void);
void addToSet(struct Set *set, int element);
bool isElementInSet(int element, struct Set *set);

#endif /* set_h */
