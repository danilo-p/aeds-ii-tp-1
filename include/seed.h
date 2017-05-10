#ifndef SEED_H
#define SEED_H

typedef struct {
    unsigned int start;
    unsigned int counter;
} Seed;

Seed * createSeed(unsigned int start);

void destroySeed(Seed *seed);

unsigned int createId(Seed *seed);

#endif