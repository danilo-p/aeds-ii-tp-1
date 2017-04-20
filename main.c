#include <stdio.h>

#include "list.h"
#include "stack.h"

/**
 * @brief      Main function
 * 
 * This is the main function of the project.
 *
 * @return     0
 */
int main() {
    Stack *stack = createStack();
    Cell *cell = createCell();

    cell->data = 2;

    pushCellOnStack(stack, cell);

    printStack(stack);

    destroyStack(stack);

    stack = NULL;

    printStack(stack);

    return 0;
}