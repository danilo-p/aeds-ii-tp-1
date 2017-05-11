#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tray.h"
#include "seed.h"
#include "stack.h"

/**
 * @brief      Creates an tray.
 *
 * @param[in]  id                 The identifier
 * @param[in]  creationInstant    The creation instant
 *
 * @return     A pointer to the new tray
 */
Tray * createTray(unsigned int id, int creationInstant) {
    Tray * newTray = malloc(sizeof(Tray));

    newTray->id = id;
    newTray->creationInstant = creationInstant;

    return newTray;
}

/**
 * @brief      Function for printing tray data
 *
 * @param      data  The tray in void *
 */
void printTray(void *data) {
    Tray *tray = (Tray *) data;

    printf("(Tray)\n");
    printf("id: %d\n", tray->id);
    printf("creationInstant: %d\n", tray->creationInstant);
}

/**
 * @brief      Insert a new tray at the given stack
 *
 * @param      stack    The stack
 * @param      newTray  The new tray
 */
void insertNewTray(Stack *stack, Tray *newTray) {
    pushCellOnStack(stack, createCell((void *) newTray));
}

/**
 * @brief      Insert new trays on the stacks
 *
 *             Used to insert new trays on the stacks
 *
 * @param      stacks           The stacks
 * @param[in]  length           The length
 * @param[in]  newTraysAmount   The new trays amount
 * @param[in]  creationInstant  The creation instant
 * @param      seed             The seed
 */
void insertNewTrays(Stack *stacks[], int length, int newTraysAmount,
        int creationInstant, Seed *seed) {
    int i = 0;

    while(newTraysAmount > 0) {
        int lessUsedStack = 0;

        for(i = 0; i < length; i++) {
            if(stacks[lessUsedStack]->list->size > stacks[i]->list->size) {
                lessUsedStack = i;
            }
        }

        if (!isStackFull(stacks[lessUsedStack])) {
            insertNewTray(stacks[lessUsedStack], createTray(createId(seed),
                creationInstant));
        }

        newTraysAmount--;
    }
}

/**
 * @brief      Destroys a tray
 *
 * @param      data  The data
 */
void destroyTray(void *data) {
    Tray *tray = (Tray *) data;
    free(tray);
}