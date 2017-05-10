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
    /** Maximum size of the queue. Negative means no maximum size. */
    int maxSize;
};

typedef struct queue Queue;

Queue * createQueue(int maxSize);

void createQueues(Queue *queues[], int length, int maxSize);

void destroyQueue(Queue *queue, void (* destructor)(void *));

void destroyQueues(Queue *queues[], int length, void (* destructor)(void *));

void pushCellOnQueue(Queue *queue, Cell *cell);

Cell * popCellFromQueue(Queue *queue);

void printQueue(Queue *queue, void (* print)(void *));

void printQueues(Queue *queues[], int length, void (* print)(void *));

void spreadQueueOnQueues(Queue *queue, Queue *queues[], int queuesLength);

Queue * pickCellsfromQueues(Queue *queues[], int length);

#endif