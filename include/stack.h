#include "list.h"

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
    /** Maximum size of the stack */
    int max_size;
};

typedef struct stack Stack;

Stack * createStack();

void pushCell(Stack *stack, Cell *cell);

Cell * popCell(Stack *stack);

void printStack(Stack *stack);

#endif