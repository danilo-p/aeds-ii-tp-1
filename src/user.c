#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "user.h"
#include "seed.h"
#include "queue.h"
#include "cell.h"

/**
 * @brief      Creates an user.
 *
 * @param[in]  id               The identifier
 * @param[in]  creationInstant  The creation instant
 *
 * @return     A pointer to the new user
 */
User * createUser(unsigned int id, int creationInstant) {
    User * newUser = malloc(sizeof(User));

    newUser->id = id;
    newUser->creationInstant = creationInstant;
    /** The finishedInstant of a new user is set to the given creationInstant. */
    newUser->finishedInstant = creationInstant;

    return newUser;
}

/**
 * @brief      Function for printing user data
 *
 * @param      data  The user in void *
 */
void printUser(void *data) {
    User *user = (User *) data;

    printf("(User)\n");
    printf("id: %d\n", user->id);
    printf("creationInstant: %d\n", user->creationInstant);
    /**
     * This function only prints the finishedInstant if it is different from the
     * creationInstant. Being different means that the user is done with the
     * restaurant services.
     */
    if(user->finishedInstant != user->creationInstant) {
        printf("finishedInstant: %d\n", user->finishedInstant);
    }
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
 *             Useful for adding a lot of users on an array of queues.
 *
 * @param      queues           The queues
 * @param[in]  length           The length
 * @param[in]  newUsersAmount   The new users amount
 * @param[in]  creationInstant  The creation instant
 * @param      seed             The seed
 */
void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant, Seed *seed) {
    int i = 0;

    while(newUsersAmount > 0) {

        int lessUsedQueue = 0;
        for(i = 0; i < length; i++) {
            if(getQueueSize(queues[lessUsedQueue]) > getQueueSize(queues[i])) {
                lessUsedQueue = i;
            }
        }

        insertNewUser(queues[lessUsedQueue], createUser(createId(seed), creationInstant));
        newUsersAmount--;
    }
}

/**
 * @brief      Destroys a user
 *
 * @param      data  The data
 */
void destroyUser(void *data) {
    User *user = (User *) data;
    free(user);
}

/**
 * @brief      Gets the time user spent average
 *
 *             Used to calculate the average of time spent using the restaurant.
 *
 * @param      users      The users
 * @param[in]  timeStart  The time start
 *
 * @return     The time user spent average
 */
float getTimeUserSpentAverage(Queue **users, int timeStart) {
    Queue *aux = createQueue((*users)->maxSize);
    int sum = 0;

    while(!isQueueEmpty(*users)) {
        Cell *userCell = popCellFromQueue(*users);

        User *user = (User *) userCell->data;

        sum += user->finishedInstant - user->creationInstant;

        pushCellOnQueue(aux, userCell);
    }

    destroyQueue(*users, destroyUser);

    *users = aux;

    return (float) sum/getQueueSize(aux);
}