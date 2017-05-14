#ifndef SEED_H
#define SEED_H

/**
 * @brief      Structure for a seed
 *
 *             This structure is responsible for storing a seed data. It is used
 *             to generate unique ids based on the seed info.
 */
struct seed {
    /** Start number for the counter */
    unsigned int start;
    /** Stores the current count of the ids */
    unsigned int counter;
};

typedef struct seed Seed;

Seed * createSeed(unsigned int start);

void destroySeed(Seed *seed);

unsigned int createId(Seed *seed);

void printSeed(Seed *seed);

#endif