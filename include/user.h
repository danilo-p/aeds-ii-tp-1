#include "queue.h"
#include "seed.h"

#ifndef USER_H
#define USER_H

/**
 * @brief      Structure of a user
 */
struct user {
    /** The user unique identifier */
    unsigned int id;
    /** The instant that the user was created */
    int creationInstant;
    /** The instant that the user finalized the restaurant services. */
    int finishedInstant;
};

typedef struct user User;

User * createUser(unsigned int id, int creationInstant);

void printUser(void *data);

void insertNewUser(Queue *queue, User *newUser);

void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant, Seed *seed);

void destroyUser(void *data);

float getTimeUserSpentAverage(Queue **users, int timeStart);

#endif