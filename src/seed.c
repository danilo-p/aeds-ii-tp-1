#include <stdio.h>
#include <stdlib.h>

#include "seed.h"

/**
 * @brief      Creates a new seed
 *
 *             Complexity: O(1)
 *
 * @param[in]  start  The start of the count
 *
 * @return     The created seed
 */
Seed * createSeed(unsigned int start) {
    Seed *seed = malloc(sizeof(Seed));

    seed->start = start;
    seed->counter = start;

    return seed;
}

/**
 * @brief      Destroy a seed
 *
 *             Complexity: O(1)
 *
 * @param      seed  The seed
 */
void destroySeed(Seed *seed) {
    free(seed);
}

/**
 * @brief      Creates an identifier
 *
 *             Complexity: O(1)
 *
 * @param[in]  seed  The seed
 *
 * @return     The created identifier
 */
unsigned int createId(Seed *seed) {
    return ++seed->counter;
}

/**
 * @brief      Prints a seed data
 * 
 *             Complexity: O(1)
 *
 * @param      seed  The seed
 */
void printSeed(Seed *seed) {
    printf("start: %d\n", seed->start);
    printf("counter: %d\n", seed->counter);
}