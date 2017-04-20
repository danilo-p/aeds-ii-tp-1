#ifndef CELL_H
#define CELL_H

/**
 * @brief      Cell structure
 *
 *             This struct is used on the list as cell.
 */
struct cell {
    /** Next cell on the list */
    struct cell *next;
    /** Stored data */
    int data;
};

typedef struct cell Cell;

Cell * createCell();

void destroyCell(Cell *cell);

void printCell(Cell *cell);

#endif
