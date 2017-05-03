#include <stdio.h>
#include <stdlib.h>

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

    char data[] = "Danilo Pimentel";

    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));

    printQueue(queue);

    printf("\nRemoving Elements\n");

    destroyCell(popCellFromQueue(queue));
    destroyCell(popCellFromQueue(queue));
    destroyCell(popCellFromQueue(queue));

    printQueue(queue);

    printf("\nInserting Elements\n");
    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));
    pushCellOnQueue(queue, createCell((void *) &(data)));

    printQueue(queue);

    destroyQueue(queue);

    printf("\nEnd\n");

    return 0;
}