#ifndef CELL_H
#define CELL_H

/**
 * @brief      Cell structure
 *
 *             Structure for a cell. This is used to implement the linked list.
 */
struct cell {
    /** Next cell on the list */
    struct cell *next;
    /** Stored data */
    void *data;
};

typedef struct cell Cell;

Cell * createCell(void *data);

void destroyCell(Cell *cell, void (* destructor)(void *));

void printCell(Cell *cell, void (* print)(void *));

#endif
