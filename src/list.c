#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "cell.h"

/**
 * @brief      Create a List
 *
 *             This function create a empty list. The first item and size is set
 *             to NULL and 0, respectively.
 *
 *             Complexity: O(1)
 *
 * @return     Returns the pointer to the created list
 */
List * createList() {
    List *list = malloc(sizeof(List));

    list->first = NULL;
    list->size = 0;

    return list;
}

/**
 * @brief      Create empty lists on the given array
 *
 *             Useful for creating a lot of new lists.
 *
 *             n: the lists array length
 *             Complexity: O(n)
 *
 * @param      lists   The lists array
 * @param[in]  length  The length of the lists array
 */
void createLists(List *lists[], int length) {
    int i;

    for(i = 0; i < length; i++) {
        lists[i] = createList();
    }
}

/**
 * @brief      Destroy the given list
 *
 *             Destroy all cells and free the space of the list. Pass the
 *             appropriated destructor for the cells data.
 *
 *             n: the list size
 *             Complexity: O(n²). The loop will execute the removeCellFromList n
 *             times, that is O(n).
 *
 * @param      list        The list
 * @param[in]  destructor  The destructor for the cells data
 */
void destroyList(List *list, void (* destructor)(void *)) {
    for (int i = list->size; i > 0; i--) {
        destroyCell(removeCellFromList(list, i-1), destructor);
    }

    free(list);
}


/**
 * @brief      Calculates the potition.
 *
 *             Calculates the position of something based on the size.
 *
 *             Complexity: O(1)
 *
 * @param[in]  position  The position
 * @param[in]  size      The size
 *
 * @return     The calculated position.
 */
int calculatePotition(int position, int size) {
    /**
     * If the position is negative, it will be interpreted that the cell have to
     * be inserted on the x position before the end of the list.
     */
    if (position < 0) {
        position = size + position;
    }

    /**
     * If the given position is greater than the size of the list, it will be
     * reassigned to the end of the list.
     */
    if(size < position) {
        position = size;
    }

    return position;
}

/**
 * @brief      Insert a Cell on the given List
 *
 *             This function will insert a cell in a determined position of the
 *             given list.
 *
 *             n: the cell position
 *             Complexity: O(n)
 *
 * @param      list      List to insert the given cell
 * @param      cell      The cell
 * @param[in]  position  Position that the cell will be inserted
 *
 * @return     The position that the cell was inserted
 */
int insertCellOnList(List *list, Cell *cell, int position) {
    int counter = 0;
    Cell *previous = NULL, *current = NULL;

    position = calculatePotition(position, list->size);

    current = list->first;

    /*
     * This loop will search the given position over the list iterating on the
     * cells. Once it arrive to the position, the "current" pointer will be
     * pointing to the cell that is on the given position.
     */
    while (counter < position) {
        previous = current;
        current = current->next;
        counter++;
    }

    /*
     * There are 3 cases to be treated. The first, last or middle position.
     *
     * First position: current will point to the first cell and previous will be
     * NULL. list->first will be set to the new cell and if the list size is
     * greater than 0, the cell->next have to point to the old first cell.
     *
     * Last position: current will be NULL and previous to the last element.
     * previous->next have to be set to cell. As cell->next is NULL by default,
     * nothing will be done.
     *
     * Middle position: current and previous will be pointing to cells on the
     * list. previous->next have to point to cell. cell->next have to point to
     * current.
     */

    /* First position */
    if(previous == NULL) {
        list->first = cell;

        /*
         * If the list is empty, current will be NULL. So assigning it to
         * cell->next will work the same way.
         */
        cell->next = current;
    }
    /* Last position */
    else if(previous != NULL && current == NULL) {
        previous->next = cell;
    }
    /* The list has 2 or more items */
    else {
        previous->next = cell;
        cell->next = current;
    }

    list->size++;

    return position;
}

/**
 * @brief      Removes a Cell from the given List
 *
 *             This function will remove a cell in a determined position of the
 *             given list.
 *
 *             n: the cell position
 *             Complexity: O(n)
 *
 * @param      list      The list
 * @param[in]  position  The position of the cell to be removed
 *
 * @return     The removed cell
 */
Cell * removeCellFromList(List *list, int position) {
    int counter = 0;
    Cell *previous = NULL, *current = NULL;

    position = calculatePotition(position, list->size);

    /*
     * If the position is equal to the size, it will be trying to remove a cell
     * that dont exist. With that, we can presume that the cell to be removed is
     * the last.
     */
    if(position == list->size) {
        position = list->size - 1;
    }

    current = list->first;

    /* 
     * This loop will search the given position over the list iterating on the
     * cells. Once it arrive to the position, the "current" pointer will be
     * pointing to the cell that is on the given position.
     */
    while (counter < position) {
        previous = current;
        current = current->next;
        counter++;
    }

    /*
     * There are 3 cases to be treated. The first, last or middle position.
     *
     * First position: current will point to the first cell and previous will be
     * NULL. list->first will be set to the current->next.
     *
     * Last position: The difference of the last position to the insertCell
     * function is that here, if the size of the list is x, you cant remove the
     * cell that is on the position x. On insert funciton, it would be a valid
     * position, because it would sign that the cell have to be the last cell.
     * Here, last position means the x-1 position. In this case, current will
     * be pointing to the last cell of the list. With that, current->next will
     * be NULL. previous->next have to be set to NULL.
     *
     * Middle position: current and previous will be pointing to cells on the
     * list. previous->next have to point to current->next.
     */


    /* First position */
    if(previous == NULL) {
        /*
         * If the list is empty, current will be NULL. If is that the case, the
         * list have no cells to be removed and nothing have to be done.
         */
        if(current != NULL) {
            list->first = current->next;
        }
    }
    /* Last position */
    else if(previous != NULL && current != NULL && current->next == NULL) {
        previous->next = NULL;
    }
    /* The list has 2 or more items */
    else {
        previous->next = current->next;
    }

    /* 
     * If the list is empty, there is no reason to decrease the size, because
     * any cell was removed.
     */
    if(list->size > 0) {
        list->size--;
    }

    return current;
}

/**
 * @brief      Print a List
 *
 *             This function will print the content of a list. It prints the
 *             position and the data of each cell.
 *
 *             n: the list size
 *             Complexity: O(n).
 *
 * @param[in]  list   Pointer to the list
 * @param[in]  print  The function for printing the cell data
 */
void printList(List *list, void (* print)(void *)) {
    int counter = 0;

    printf("%d Cells\n\n", list->size);

    if(list) {
        Cell *current = list->first;

        while (counter < list->size) {
            printf("Cell %d\n", counter);
            printCell(current, print);
            current = current->next;
            counter++;
            printf("\n");
        }
    }
}