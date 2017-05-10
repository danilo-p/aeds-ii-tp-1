#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

/**
 * @brief      Create a Cell
 *
 *             This funciton will create a new empty cell. The next item will be
 *             set to NULL and the stored data will be set to 0.
 *
 * @param[in]  data  Pointer to the data
 *
 * @return     Returns a pointer to a new empty Cell.
 */
Cell * createCell(void *data) {
    Cell *cell = malloc(sizeof(Cell));

    cell->next = NULL;
    cell->data = data;

    return cell;
}

/**
 * @brief      Destroy a cell
 *
 *             Take care while destroying a cell. Remember to set the pointer to
 *             the destroyed cell to NULL to avoid Segmentation Faults.
 *
 * @param      cell        The cell
 * @param[in]  destructor  The destructor for the cell data
 */
void destroyCell(Cell *cell, void (* destructor)(void *)) {
    destructor(cell->data);
    free(cell);
}

/**
 * @brief      Print the cell
 *
 * @param      cell   The cell
 * @param[in]  print  The function for printing the cell data
 */
void printCell(Cell *cell, void (* print)(void *)) {
    print(cell->data);
}
