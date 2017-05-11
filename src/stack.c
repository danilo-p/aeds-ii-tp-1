#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "list.h"
#include "cell.h"

/**
 * @brief      Creates a empty stack
 *
 *             This function create a empty stack with an empty list and the
 *             given maxSize. If the maxSize specified is less than 0, the stack
 *             dont have limit.
 *
 * @param[in]  maxSize  The maximum size of the Stack
 *
 * @return     Pointer to the created stack
 */
Stack * createStack(int maxSize) {
    Stack *stack = malloc(sizeof(Stack));

    stack->list = createList();
    stack->maxSize = maxSize;

    return stack;
}

/**
 * @brief      Create empty stacks on the given array
 *
 * @param      stacks   The stacks array
 * @param[in]  length   The length of the array
 * @param[in]  maxSize  The maximum size of the stack
 */
void createStacks(Stack *stacks[], int length, int maxSize) {
    int i;

    for(i = 0; i < length; i++) {
        stacks[i] = createStack(maxSize);
    }
}

/**
 * @brief      Destroy the given stack
 *
 *             Destroy the list of the stack and free the space.
 *
 *             Take care while destroying a stack. Remember to set the pointer
 *             to the destroyed stack to NULL to avoid Segmentation Faults.
 *
 * @param      stack       The stack
 * @param[in]  destructor  The destructor
 */
void destroyStack(Stack *stack, void (* destructor)(void *)) {
    destroyList(stack->list, destructor);

    free(stack);
}

/**
 * @brief      Destroy all the stacks from the given array
 *
 * @param      stacks      The stacks array
 * @param[in]  length      The length of the array
 * @param[in]  destructor  The destructor
 */
void destroyStacks(Stack *stacks[], int length, void (* destructor)(void *)) {
    int i;

    for(i = 0; i < length; i++) {
        destroyStack(stacks[i], destructor);
    }
}

/**
 * @brief      Determines if stack full.
 *
 * @param      stack  The stack
 *
 * @return     True if stack full, False otherwise.
 */
bool isStackFull(Stack *stack) {
    return (stack->list->size == stack->maxSize);
}

/**
 * @brief      Determines if stack empty.
 *
 * @param      stack  The stack
 *
 * @return     True if stack empty, False otherwise.
 */
bool isStackEmpty(Stack *stack) {
    return (stack->list->size == 0);
}

/**
 * @brief      Determines if stack infinity.
 *
 * @param      stack  The stack
 *
 * @return     True if stack infinity, False otherwise.
 */
bool isStackInfinity(Stack *stack) {
    return (stack->maxSize < 0);
}

/**
 * @brief      Push a cell on the given stack
 *
 * @param      stack  The stack
 * @param      cell   The cell
 */
void pushCellOnStack(Stack *stack, Cell *cell) {
    if (isStackInfinity(stack) || !isStackFull(stack)) {
        insertCellOnList(stack->list, cell, stack->list->size);
    }
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
 * @param[in]  print  The function for printing the cell data
 */
void printStack(Stack *stack, void (* print)(void *)) {
    if(stack) {
        printList(stack->list, print);
    }
}

/**
 * @brief      Print the given stacks
 *
 * @param      stacks  The stacks
 * @param[in]  length  The length
 * @param[in]  print   The function for printing the cell data
 */
void printStacks(Stack *stacks[], int length, void (* print)(void *)) {
    int i;

    for (i = 0; i < length; ++i) {
        printf("\nStack %d\n", i);
        printStack(stacks[i], print);
    }
}

/**
 * @brief      Pick cells from the given stacks
 *
 *             This function pops the cells of stacks and add on the given stack
 *
 * @param      dest    The destination
 * @param      stacks  The stacks array
 * @param[in]  length  The length of the stacks array
 */
void pickCellsfromStacks(Stack *dest, Stack *stacks[], int length) {
    for (int i = 0; i < length && !isStackFull(dest); i++) {
        Cell *picked = NULL;
        if( (picked = popCellFromStack(stacks[i])) != NULL) {
            pushCellOnStack(dest, picked);
        }
    }
}