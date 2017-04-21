#include <stdio.h>

#include "queue.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the project.
 *
 * @return     0
 */
int main() {
    printf("Start\n");

    printf("\nInitial Queue\n");

    Queue *queue = createQueue();

    pushCellOnQueue(queue, createCell(1));
    pushCellOnQueue(queue, createCell(2));
    pushCellOnQueue(queue, createCell(3));
    pushCellOnQueue(queue, createCell(4));
    pushCellOnQueue(queue, createCell(5));
    pushCellOnQueue(queue, createCell(6));

    printQueue(queue);

    printf("\nRemoving Elements\n");

    destroyCell(popCellFromQueue(queue));
    destroyCell(popCellFromQueue(queue));
    destroyCell(popCellFromQueue(queue));

    printQueue(queue);

    printf("\nInserting Elements\n");
    pushCellOnQueue(queue, createCell(7));
    pushCellOnQueue(queue, createCell(8));
    pushCellOnQueue(queue, createCell(9));

    printQueue(queue);

    destroyQueue(queue);

    printf("\nEnd\n");

    return 0;
}