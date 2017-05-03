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
    void *data;
};

typedef struct cell Cell;

Cell * createCell(void *data);

void destroyCell(Cell *cell);

#endif
