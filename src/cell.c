#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

/**
 * @brief      Create a Cell
 *
 *             This funciton will create a new empty cell. The next item will be
 *             set to NULL and the stored data will be set to 0.
 *
 * @return     Returns a pointer to a new empty Cell.
 */
Cell * createCell() {
    Cell *cell = malloc(sizeof(Cell));

    cell->next = NULL;
    cell->data = 0;

    return cell;
}

/**
 * @brief      Destroy a cell
 *
 *             Take care while destroying a cell. Remember to set the pointer to
 *             the destroyed cell to NULL to avoid Segmentation Faults.
 *
 * @param      cell  The cell
 */
void destroyCell(Cell *cell) {
    free(cell);
}

/**
 * @brief      Print the given cell
 *
 * @param      cell  The cell
 */
void printCell(Cell *cell) {
    if(cell) {
        printf("data: %d\n", cell->data);
    }
}