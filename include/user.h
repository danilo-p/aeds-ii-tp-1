#include "queue.h"
#include "seed.h"

#ifndef USER_H
#define USER_H

typedef struct user {
    unsigned int id;
    int creationInstant;
} User;

User * createUser(unsigned int id, int creationInstant);

void printUser(void * user);

void insertNewUser(Queue *queue, User *newUser);

void insertNewUsers(Queue *queues[], int length, int newUsersAmount,
        int creationInstant, Seed *seed);

void destroyUser(void *data);

#endif