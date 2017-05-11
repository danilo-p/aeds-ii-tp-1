#include <stdbool.h>

#include "stack.h"
#include "seed.h"

#ifndef TRAY_H
#define TRAY_H

typedef struct {
    unsigned int id;
    int creationInstant;
} Tray;

Tray * createTray(unsigned int id, int creationInstant);

void printTray(void *data);

void insertNewTray(Stack *stack, Tray *newTray);

void insertNewTrays(Stack *stacks[], int length, int newTraysAmount,
        int creationInstant, Seed *seed);

void destroyTray(void *data);

#endif