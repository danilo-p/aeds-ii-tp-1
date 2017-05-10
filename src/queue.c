#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "list.h"
#include "cell.h"

/**
 * @brief      Creates a empty queue
 *
 *             This function create a empty queue with an empty list and the
 *             given maxSize. If the maxSize specified is less than 0, the queue
 *             dont have limit.
 *
 * @param[in]  maxSize  The maximum size of the Queue
 *
 * @return     Pointer to the created queue
 */
Queue * createQueue(int maxSize) {
    Queue *queue = malloc(sizeof(Queue));

    queue->list = createList();
    queue->maxSize = maxSize;

    return queue;
}

/**
 * @brief      Create empty queues on the given array
 *
 * @param      queues   The queues
 * @param[in]  length   The length of the queues array
 * @param[in]  maxSize  The maximum size of the queue
 */
void createQueues(Queue *queues[], int length, int maxSize) {
    int i;

    for(i = 0; i < length; i++) {
        queues[i] = createQueue(maxSize);
    }
}

/**
 * @brief      Destroy the given queue
 *
 *             Destroy the list of the queue and free the space.
 *
 *             Take care while destroying a queue. Remember to set the pointer
 *             to the destroyed queue to NULL to avoid Segmentation Faults.
 *
 * @param      queue       The queue
 * @param[in]  destructor  The destructor
 */
void destroyQueue(Queue *queue, void (* destructor)(void *)) {
    destroyList(queue->list, destructor);

    free(queue);
}

/**
 * @brief      Destroy all the queues from the given array
 *
 * @param      queues      The queues array
 * @param[in]  length      The length of the array
 * @param[in]  destructor  The destructor
 */
void destroyQueues(Queue *queues[], int length, void (* destructor)(void *)) {
    int i;

    for(i = 0; i < length; i++) {
        destroyQueue(queues[i], destructor);
    }
}

/**
 * @brief      Push a cell on the given queue
 *
 * @param      queue  The queue
 * @param      cell   The cell
 */
void pushCellOnQueue(Queue *queue, Cell *cell) {
    if(cell == NULL) {
        printf("\n\n\n\nQUE PRAGA\n\n\n\n");
    }

    if (queue->maxSize < 0 || queue->list->size < queue->maxSize) {
        insertCellOnList(queue->list, cell, queue->list->size);
    }
}

/**
 * @brief      Pop a cell from the given queue
 *
 * @param      queue  The queue
 *
 * @return     The popped cell
 */
Cell * popCellFromQueue(Queue *queue) {
    return removeCellFromList(queue->list, 0);
}

/**
 * @brief      Print the given queue
 *
 * @param      queue  The queue
 * @param[in]  print  The function for printing the queue cell's data
 */
void printQueue(Queue *queue, void (* print)(void *)) {
    if(queue) {
        printList(queue->list, print);
    }
}

void printQueues(Queue *queues[], int length, void (* print)(void *)) {
    int i;

    for (i = 0; i < length; ++i) {
        printf("\nQueue %d\n\n", i);
        printQueue(queues[i], print);
    }
}

/**
 * @brief      Spread the queue's cells on a group of other queues
 * 
 *             This function consumes the queue and pushes the cells on the queues
 *             on the order that they arrive on the queues array.
 *
 * @param      queue         The queue to be spreaded
 * @param      queues        The queues group
 * @param[in]  queuesLength  The queues group length
 */
void spreadQueueOnQueues(Queue *queue, Queue *queues[], int queuesLength) {
    int queuesIndex = 0;
    while (queue->list->size > 0) {
        Cell *aux = popCellFromQueue(queue);
        pushCellOnQueue(queues[queuesIndex%queuesLength], aux);
        queuesIndex++;
    }
}

/**
 * @brief      Pick cells from the given queues
 *
 *             This function pops the first cell of queues and add on the given
 *             queue
 *
 * @param      dest    The destination
 * @param      queues  The queues array
 * @param[in]  length  The length of the queues array
 */
void pickCellsfromQueues(Queue *dest, Queue *queues[], int length) {
    for (int i = 0; i < length; i++) {
        Cell *picked = NULL;
        if( (picked = popCellFromQueue(queues[i])) != NULL) {
            pushCellOnQueue(dest, picked);
        }
    }
}