#include <stdbool.h>

#include "stack.h"
#include "seed.h"

#ifndef TRAY_H
#define TRAY_H

/**
 * @brief      Structure for the tray
 *
 *             As the tray is used only for populating the stacks of the
 *             restaurant, we don't need to store other data. This one is just
 *             for control purposes.
 */
struct tray {
    /** The tray unique identifier */
    unsigned int id;
    /** The instant that the tray was created */
    int creationInstant;
};

typedef struct tray Tray;

Tray * createTray(unsigned int id, int creationInstant);

void printTray(void *data);

void insertNewTray(Stack *stack, Tray *newTray);

void insertNewTrays(Stack *stacks[], int length, int newTraysAmount,
    int creationInstant, Seed *seed);

void destroyTray(void *data);

#endif