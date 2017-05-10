#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "seed.h"
#include "queue.h"

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

    return newUser;
}

/**
 * @brief      Function for printing user data
 *
 * @param      user  The user
 */
void printUser(void * user) {
    User *aux = (User *) user;

    printf("id: %d\n", aux->id);
    printf("creationInstant: %d\n", aux->creationInstant);
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
 * @param      seed             The seed
 */
void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant, Seed *seed) {
    int i = 0, j;

    while(newUsersAmount > 0) {

        int lessUsedQueue = 0;
        for(j = 0; j < length; j++) {
            if(queues[lessUsedQueue]->list->size > queues[j]->list->size) {
                lessUsedQueue = j;
            }
        }

        insertNewUser(queues[lessUsedQueue], createUser(createId(seed), creationInstant));
        newUsersAmount--;

        i++;
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