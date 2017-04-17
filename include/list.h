#ifndef LIST_H
#define LIST_H

/**
 * @brief      Cell structure
 * 
 * This struct is used on the list as cell.
 */
struct cell {
    /** Next cell on the list */
    struct cell *next;
    /** Stored data */
    int data;
};

typedef struct cell Cell;

/**
 * @brief      List structure
 * 
 * This will be the structure of the list.
 */
struct list {
    /** Pointer to the first item on the list */
    Cell *first;
    /** Size of the list */
    int size;
};

typedef struct list List;

void initializeList(List *list);

void initializeCell(Cell *cell);

void insertCell(List *list, Cell *cell, int position);

void removeCell(List *list, int position);

void printList(List list);

#endif
