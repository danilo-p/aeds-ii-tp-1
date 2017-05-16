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
 *             Complexity: O(1)
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
 *             n: the queues array length
 *             Complexity: O(n)
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
 *             Destroy the list of the queue and free the space. Also, destroy
 *             the cells data with the given destructor.
 *
 *             n: the queue size
 *             Complexity: O(n²)
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
 *             n: the queues array length
 *             m: the greatest queue size
 *             Complexity: O(nm²). The loop will execute destroyQueue n times,
 *             that is O(m²). In the worst case, all the queues have the same
 *             size, so we consider here the greatest size found on the queues
 *             array.
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
 * @brief      Gets the queue size.
 *
 *             Complexity: O(1)
 *
 * @param      queue  The queue
 *
 * @return     The queue size.
 */
int getQueueSize(Queue *queue) {
    return queue->list->size;
}

/**
 * @brief      Determines if queue is full
 *
 *             Complexity: O(1)
 *
 * @param      queue  The queue
 *
 * @return     True if queue full, False otherwise.
 */
bool isQueueFull(Queue *queue) {
    return (getQueueSize(queue) == queue->maxSize);
}

/**
 * @brief      Determines if queue is empty
 *
 *             Complexity: O(1)
 *
 * @param      queue  The queue
 *
 * @return     True if queue empty, False otherwise.
 */
bool isQueueEmpty(Queue *queue) {
    return (getQueueSize(queue) == 0);
}

/**
 * @brief      Determines if queue is infinity
 * 
 *             Complexity: O(1)
 *
 * @param      queue  The queue
 *
 * @return     True if queue infinity, False otherwise.
 */
bool isQueueInfinity(Queue *queue) {
    return (queue->maxSize < 0);
}

/**
 * @brief      Push a cell on the given queue
 *
 *             n: the queue size
 *             Complexity: O(n)
 *
 * @param      queue  The queue
 * @param      cell   The cell
 */
void pushCellOnQueue(Queue *queue, Cell *cell) {
    if (isQueueInfinity(queue) || !isQueueFull(queue)) {
        insertCellOnList(queue->list, cell, getQueueSize(queue));
    }
}

/**
 * @brief      Pop a cell from the given queue
 * 
 *             Complexity: O(1). removeCellFromList complexity is O(n), and n is
 *             the position that the cell will be inserted. In this case, we are
 *             inserting cells at the first position, so it will be O(1).
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
 *             n: the queue size
 *             Complexity: O(n)
 *
 * @param      queue  The queue
 * @param[in]  print  The function for printing the queue cell's data
 */
void printQueue(Queue *queue, void (* print)(void *)) {
    if(queue) {
        printList(queue->list, print);
    }
}

/**
 * @brief      Print all the queues from the given array
 *
 *             n: the queues array length
 *             m: the greatest queue size
 *             Complexity: O(nm). The loop will execute printQueue n times,
 *             that is O(m). In the worst case, all the queues have the same
 *             size, so we consider here the greatest size found on the queues
 *             array.
 *
 * @param      queues  The queues
 * @param[in]  length  The length
 * @param[in]  print   The print
 */
void printQueues(Queue *queues[], int length, void (* print)(void *)) {
    int i;

    for (i = 0; i < length; ++i) {
        printf("\nQueue %d\n", i);
        printQueue(queues[i], print);
    }
}

/**
 * @brief      Spread the queue's cells on a group of other queues
 *
 *             This function consumes the queue and pushes the cells on the
 *             queues on the order that they arrive on the queues array.
 *
 *             n: the queue size
 *             m: the greatest queue size on the queues array
 *             Complexity: O(nm). In the worst case, this function will consume
 *             all the queue cells. So the loop will execute n times. The loop
 *             execute pushCellOnQueue n times, that is O(m).
 *
 * @param      queue         The queue to be spreaded
 * @param      queues        The queues group
 * @param[in]  queuesLength  The queues group length
 * @param[in]  spreadAmount  The amount of cells to spread
 */
void spreadQueueOnQueues(Queue *queue, Queue *queues[], int queuesLength, int spreadAmount) {
    int queuesIndex = 0;
    int queueInitialLength = getQueueSize(queue);
    while (!isQueueEmpty(queue) && queueInitialLength - spreadAmount < getQueueSize(queue)) {
        Cell *aux = popCellFromQueue(queue);
        pushCellOnQueue(queues[queuesIndex % queuesLength], aux);
        queuesIndex++;
    }
}

/**
 * @brief      Pick cells from the given queues
 *
 *             This function pops the first cell of queues and add on the given
 *             queue.
 *
 *             n: the length of the queues array
 *             m: the length of the dest queue. On the worst case, the dest
 *             queue is infinity, so the current size have to be considered.
 *             Complexity: O(mn + n²).
 *
 * @param      dest    The destination
 * @param      queues  The queues array
 * @param[in]  length  The length of the queues array
 */
void pickCellsfromQueues(Queue *dest, Queue *queues[], int length) {
    for (int i = 0; i < length && !isQueueFull(dest); i++) {
        Cell *picked = NULL;
        if( (picked = popCellFromQueue(queues[i])) != NULL) {
            pushCellOnQueue(dest, picked);
        }
    }
}