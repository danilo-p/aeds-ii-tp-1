#include "list.h"
#include "cell.h"

#ifndef STACK_H
#define STACK_H

/**
 * @brief      Stack structure
 *
 *             This struct stores all the required info for a stack.
 */
struct stack {
    /** List that is used to store the stack elements */
    List *list;
    /** Maximum size of the stack. Negative means no maximum size. */
    int maxSize;
};

typedef struct stack Stack;

Stack * createStack(int maxSize);

void createStacks(Stack *stacks[], int length, int maxSize);

void destroyStack(Stack *stack);

void pushCellOnStack(Stack *stack, Cell *cell);

Cell * popCellFromStack(Stack *stack);

void printStack(Stack *stack);

#endif