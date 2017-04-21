#include "list.h"
#include "cell.h"

#ifndef QUEUE_H
#define QUEUE_H

/**
 * @brief      Queue structure
 *
 *             This struct stores all the required info for a queue.
 */
struct queue {
    /** List that is used to store the queue elements */
    List *list;
    /** Maximum size of the queue */
    int max_size;
};

typedef struct queue Queue;

Queue * createQueue();

void destroyQueue(Queue *queue);

void pushCellOnQueue(Queue *queue, Cell *cell);

Cell * popCellFromQueue(Queue *queue);

void printQueue(Queue *queue);

#endif