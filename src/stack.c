#include <stdlib.h>

#include "stack.h"
#include "list.h"

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
 * @brief      Push a cell on the given stack.
 *
 * @param      stack  The stack
 * @param      cell   The cell
 */
void pushCell(Stack *stack, Cell *cell) {
    insertCell(stack->list, cell, stack->list->size);
}

/**
 * @brief      Pop a cell from the given stack
 *
 * @param      stack  The stack
 *
 * @return     The popped cell
 */
Cell * popCell(Stack *stack) {
    return removeCell(stack->list, stack->list->size-1);
}

/**
 * @brief      Print the given stack
 *
 * @param      stack  The stack
 */
void printStack(Stack *stack) {
    printList(stack->list);
}