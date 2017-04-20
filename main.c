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
    List *list = createList();
    Cell *cell = createCell();

    insertCell(list, cell, 0);

    printList(list);

    return 0;
}