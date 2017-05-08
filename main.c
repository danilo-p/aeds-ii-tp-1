#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cell.h"
#include "queue.h"
#include "stack.h"

typedef struct user {
    int id;
    int creationInstant;
} User;

User * createUser(int creationInstant);

void insertNewUser(Queue *queue, User *newUser);

void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant);

/**
 * @brief      Main function
 *
 *             This is the main function of the length.
 *
 * @return     0
 */
int main() {
    // Quantidade de filas de ficha
    int CHECKOUT_QUEUE_AMOUNT   = 1;
    // Quantidade máxima de pessoas nas filas de ficha (negativa significa sem
    // limite)
    int CHECKOUT_QUEUE_SIZE     = -1;
    // Tempo gasto no caixa     
    int CHECKOUT_DELAY          = 1;
    // Quantidade de filas de bandeja
    int TRAY_QUEUE_AMOUNT       = 1;
    // Quantidade máxima de pessoas nas filas de bandeja (negativa significa sem
    // limite)
    int TRAY_QUEUE_SIZE     = -1;
    // Quantidade de pilhas de bandeja
    int TRAY_STACK_AMOUNT       = 1;
    // Tamanho da pilha de bandeja
    int TRAY_STACK_SIZE         = 30;
    // Quantidade de bandejas repostas nas pilhas a cada intervalo
    int TRAY_REFILL_AMOUNT      = 10;
    // Intervalo de reposição de bandejas
    int TRAY_REFILL_INTERVAL    = 12;
    // Intervalo de chegada de novos usuários
    int USER_ARRIVAL_INTERVAL   = 2;
    // Quantidade de usuários que chegam a cada intervalo
    int USER_REFILL_AMOUNT      = 4;
    // Tempo gasto para pegar uma bandeja
    int TRAY_DELAY              = 1;
    // Tempo gasto para servir um tipo de comida
    int FOOD_DELAY              = 1;
    // Tempo da simulação
    int DURATION                = 240;

    Queue *checkoutQueues[CHECKOUT_QUEUE_AMOUNT];
    Queue *trayQueues[TRAY_QUEUE_AMOUNT];
    Stack *trayStacks[TRAY_STACK_AMOUNT];

    createQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, CHECKOUT_QUEUE_SIZE);
    createQueues(trayQueues, TRAY_QUEUE_AMOUNT, TRAY_QUEUE_SIZE);
    createStacks(trayStacks, TRAY_STACK_AMOUNT, TRAY_STACK_SIZE);

    int instant;

    for(instant = 0; instant < DURATION; instant++) {
        if (instant % USER_ARRIVAL_INTERVAL == 0) {
            insertNewUsers(checkoutQueues, CHECKOUT_QUEUE_AMOUNT,
                USER_REFILL_AMOUNT, instant);
        }
    }

    // printf("Start\n");

    // printf("\nInitial Queue\n");

    // Queue *queue = createQueue();

    // char data[] = "Danilo Pimentel";

    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));

    // printQueue(queue);

    // printf("\nRemoving Elements\n");

    // destroyCell(popCellFromQueue(queue));
    // destroyCell(popCellFromQueue(queue));
    // destroyCell(popCellFromQueue(queue));

    // printQueue(queue);

    // printf("\nInserting Elements\n");
    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));
    // pushCellOnQueue(queue, createCell((void *) &(data)));

    // printQueue(queue);

    // destroyQueue(queue);

    // printf("\nEnd\n");

    return 0;
}

/**
 * @brief      Creates an user.
 *
 * @param[in]  creationInstant  The creation instant
 *
 * @return     A pointer to the new user
 */
User * createUser(int creationInstant) {
    User * newUser = malloc(sizeof(User));

    newUser->id = (int) time(NULL);
    newUser->creationInstant = creationInstant;

    return newUser;
}

/**
 * @brief      Insert a new user at the given queue
 *
 * @param      queue    The queue
 * @param      newUser  The new user
 */
void insertNewUser(Queue *queue, User *newUser) {
    pushCellOnQueue(queue, createCell((void *) newUser));
}

/**
 * @brief      Insert new users on the queues
 *
 *             Used to insert new users on the checkout queues
 *
 * @param      queues           The queues
 * @param[in]  length           The length
 * @param[in]  newUsersAmount   The new users amount
 * @param[in]  creationInstant  The creation instant
 */
void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant) {
    int i;

    while(newUsersAmount > 0) {
        insertNewUser(queues[i%length], createUser(creationInstant));
        newUsersAmount--;

        i++;
    }
}