#include "queue.h"
#include "seed.h"

#ifndef USER_H
#define USER_H

typedef struct user {
    unsigned int id;
    int creationInstant;
    int finishedInstant;
} User;

User * createUser(unsigned int id, int creationInstant);

void printUser(void *data);

void insertNewUser(Queue *queue, User *newUser);

void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant, Seed *seed);

void destroyUser(void *data);

float getTimeUserSpentAverage(Queue **users, int timeStart);

#endif