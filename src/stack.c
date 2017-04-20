#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "list.h"
#include "cell.h"

/**
 * @brief      Creates a empty stack
 *
 *             This function create a empty stack with an empty list and the
 *             given max_size. If the max_size specified is less than 0, the
 *             stack dont have limit.
 *
 * @return     Pointer to the created stack
 */
Stack * createStack() {
    Stack *stack = malloc(sizeof(Stack));

    stack->list = createList();
    stack->max_size = -1;

    return stack;
}

/**
 * @brief      Destroy the given stack
 *
 *             Destroy the list of the stack and free the space.
 *
 *             Take care while destroying a stack. Remember to set the pointer
 *             to the destroyed stack to NULL to avoid Segmentation Faults.
 *
 * @param      stack  The stack
 */
void destroyStack(Stack *stack) {
    destroyList(stack->list);

    free(stack);
}

/**
 * @brief      Push a cell on the given stack
 *
 * @param      stack  The stack
 * @param      cell   The cell
 */
void pushCellOnStack(Stack *stack, Cell *cell) {
    insertCellOnList(stack->list, cell, stack->list->size);
}

/**
 * @brief      Pop a cell from the given stack
 *
 * @param      stack  The stack
 *
 * @return     The popped cell
 */
Cell * popCellFromStack(Stack *stack) {
    return removeCellFromList(stack->list, stack->list->size-1);
}

/**
 * @brief      Print the given stack
 *
 * @param      stack  The stack
 */
void printStack(Stack *stack) {
    if(stack) {
        printList(stack->list);
    }
}