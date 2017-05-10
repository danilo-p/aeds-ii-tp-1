#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "queue.h"
#include "stack.h"
#include "seed.h"
#include "config.h"
#include "user.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the length.
 *
 * @return     0
 */
int main() {
    Seed *seed = createSeed(0);
    Queue *checkout = createQueue(CHECKOUT_QUEUE_AMOUNT);
    Queue *checkoutQueues[CHECKOUT_QUEUE_AMOUNT];
    Queue *trayQueues[TRAY_QUEUE_AMOUNT];

    createQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, CHECKOUT_QUEUE_SIZE);
    createQueues(trayQueues, TRAY_QUEUE_AMOUNT, TRAY_QUEUE_SIZE);

    int instant;

    for(instant = 0; instant < DURATION; instant++) {
        // User arrival
        if (instant % USER_ARRIVAL_INTERVAL == 0) {
            insertNewUsers(checkoutQueues, CHECKOUT_QUEUE_AMOUNT,
                USER_REFILL_AMOUNT, instant, seed);
        }

        // Checkout service
        if (instant % CHECKOUT_DELAY == 0) {
            // Remove users from the checkout
            spreadQueueOnQueues(checkout, trayQueues, TRAY_QUEUE_AMOUNT);

            // Add the next users on the checkout
            pickCellsfromQueues(checkout, checkoutQueues, CHECKOUT_QUEUE_AMOUNT);
        }
    }

    destroySeed(seed);
    destroyQueue(checkout, destroyUser);
    destroyQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, destroyUser);
    destroyQueues(trayQueues, TRAY_QUEUE_AMOUNT, destroyUser);

    return 0;
}
