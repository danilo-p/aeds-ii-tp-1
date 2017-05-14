#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

/**
 * @brief      Create a new Cell
 *
 *             This funciton will create a new cell. The next item will be set
 *             to NULL and the stored data will be set to the specified data.
 *
 *             Complexity: O(1)
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
 * @brief      Destroy a Cell
 *
 *             This function destroys the given cell. Pass the appropriated
 *             destructor for destroying the stored data.
 *
 *             Complexity: O(1)
 *
 * @param      cell        The cell
 * @param[in]  destructor  The destructor for the cell data
 */
void destroyCell(Cell *cell, void (* destructor)(void *)) {
    if(cell->data) { 
        destructor(cell->data);
    }
    free(cell);
}

/**
 * @brief      Print a cell
 *
 *             Complexity: O(1)
 *
 * @param      cell   The cell
 * @param[in]  print  The function for printing the cell data
 */
void printCell(Cell *cell, void (* print)(void *)) {
    print(cell->data);
}
