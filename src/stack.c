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
 *             Complexity: O(1)
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
 *             n: the stacks array length
 *             Complexity: O(n)
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
 *             Destroy the list of the stack and free the space. Also, destroy
 *             the cells data with the given destructor.
 *
 *             n: the stack size
 *             Complexity: O(n²)
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
 *             n: the stacks array length
 *             m: the greatest queue size
 *             Complexity: O(nm²). The loop will execute destroyQueue n times,
 *             that is O(m²). In the worst case, all the stacks have the same
 *             size, so we consider here the greatest size found on the stacks
 *             array.
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
 * @brief      Gets the stack size
 *
 *             Complexity: O(1)
 *             
 * @param      stack  The stack
 *
 * @return     The stack size.
 */
int getStackSize(Stack *stack) {
    return stack->list->size;
}

/**
 * @brief      Determines if stack is full
 *
 *             Complexity: O(1)
 *
 * @param      stack  The stack
 *
 * @return     True if stack full, False otherwise.
 */
bool isStackFull(Stack *stack) {
    return (getStackSize(stack) == stack->maxSize);
}

/**
 * @brief      Determines if stack is empty
 *
 *             Complexity: O(1)
 *
 * @param      stack  The stack
 *
 * @return     True if stack empty, False otherwise.
 */
bool isStackEmpty(Stack *stack) {
    return (getStackSize(stack) == 0);
}

/**
 * @brief      Determines if stack infinity
 *
 *             Complexity: O(1)
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
 *             n: the stack size
 *             Complexity: O(n)
 *
 * @param      stack  The stack
 * @param      cell   The cell
 */
void pushCellOnStack(Stack *stack, Cell *cell) {
    if (isStackInfinity(stack) || !isStackFull(stack)) {
        insertCellOnList(stack->list, cell, getStackSize(stack));
    }
}

/**
 * @brief      Pop a cell from the given stack
 *
 *             n: the stack size
 *             Complexity: O(n)
 *
 * @param      stack  The stack
 *
 * @return     The popped cell
 */
Cell * popCellFromStack(Stack *stack) {
    return removeCellFromList(stack->list, getStackSize(stack)-1);
}

/**
 * @brief      Print the given stack
 
 *             n: the stack size
 *             Complexity: O(n)
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
 *             n: the stacks array length
 *             m: the greatest queue size
 *             Complexity: O(nm). The loop will execute printQueue n times,
 *             that is O(m). In the worst case, all the stacks have the same
 *             size, so we consider here the greatest size found on the stacks
 *             array.
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
 * @brief      Determines if all the stacks of the given array are empty.
 *
 *             n: the stacks length
 *             Complexity: O(n)
 *
 * @param      stacks  The stacks
 * @param[in]  length  The length
 *
 * @return     True if stacks empty, False otherwise.
 */
bool isStacksEmpty(Stack *stacks[], int length) {
    bool empty = true;
    for (int i = 0; i < length; ++i) {
        if(!isStackEmpty(stacks[i])) {
            empty = false;
        }
    }
    return empty;
}

/**
 * @brief      Pick cells from the given stacks
 *
 *             This function pops the cells of stacks and add on the given stack
 *
 *             n: the length of the stacks array
 *             m: the length of the dest stack. On the worst case, the dest
 *             stack is infinity, so the current size have to be considered.
 *             Complexity: O(mn + n²).
 *
 * @param      dest    The destination
 * @param      stacks  The stacks array
 * @param[in]  length  The length of the stacks array
 */
void pickCellsfromStacks(Stack *dest, Stack *stacks[], int length) {
    int stackIndex = 0;
    while (!isStacksEmpty(stacks, length) && !isStackFull(dest)) {
        Cell *picked = NULL;
        if( (picked = popCellFromStack(stacks[stackIndex%length])) != NULL) {
            pushCellOnStack(dest, picked);
        }
        stackIndex++;
    }
}