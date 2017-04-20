#include "cell.h"

#ifndef LIST_H
#define LIST_H

/**
 * @brief      List structure
 *
 *             This will be the structure of the list.
 */
struct list {
    /** Pointer to the first item on the list */
    Cell *first;
    /** Size of the list */
    int size;
};

typedef struct list List;

List * createList();

void destroyList(List *list);

int insertCellOnList(List *list, Cell *cell, int position);

Cell * removeCellFromList(List *list, int position);

void printList(List *list);

#endif
