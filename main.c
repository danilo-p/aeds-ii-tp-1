#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cell.h"
#include "queue.h"
#include "stack.h"
#include "seed.h"
#include "config.h"
#include "user.h"
#include "tray.h"

/**
 * @brief      Main function
 *
 *             This is the main function of the length.
 *
 * @return     0
 */
int main() {
    int timeStart = 0;
    int infinityADT = -1;
    int instant;

    Seed *seed = createSeed(timeStart);

    Queue *checkout = createQueue(CHECKOUT_QUEUE_AMOUNT);

    Queue *checkoutQueues[CHECKOUT_QUEUE_AMOUNT];
    createQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, CHECKOUT_QUEUE_SIZE);

    Queue *traysStation = createQueue(TRAY_STACK_AMOUNT);

    Queue *trayQueues[TRAY_QUEUE_AMOUNT];
    createQueues(trayQueues, TRAY_QUEUE_AMOUNT, TRAY_QUEUE_SIZE);

    Stack *trayStacks[TRAY_STACK_AMOUNT];
    createStacks(trayStacks, TRAY_STACK_AMOUNT, TRAY_STACK_SIZE);

    Queue *foodQueues[FOOD_QUEUE_AMOUNT];
    createQueues(foodQueues, FOOD_QUEUE_AMOUNT, FOOD_QUEUE_SIZE);

    Queue *foodsStation[FOOD_QUEUE_AMOUNT];
    createQueues(foodsStation, FOOD_QUEUE_AMOUNT, FOOD_OPTIONS_AMOUNT);

    Queue *finishedUsers = createQueue(infinityADT);

    for(instant = timeStart; instant < DURATION; instant++) {
        // User arrival
        if (instant % USER_ARRIVAL_INTERVAL == 0) {
            insertNewUsers(checkoutQueues, CHECKOUT_QUEUE_AMOUNT,
                USER_ARRIVAL_AMOUNT, instant, seed);
        }

        // Trays refill
        if (instant % TRAY_REFILL_INTERVAL == 0) {
            insertNewTrays(trayStacks, TRAY_STACK_AMOUNT,
                TRAY_REFILL_AMOUNT * TRAY_STACK_AMOUNT, instant, seed);
        }

        // Checkout service
        if (instant % CHECKOUT_DELAY == 0) {
            // Remove users from the checkout
            spreadQueueOnQueues(checkout, trayQueues, TRAY_QUEUE_AMOUNT, getQueueSize(checkout));

            // Add the next users on the checkout
            pickCellsfromQueues(checkout, checkoutQueues, CHECKOUT_QUEUE_AMOUNT);
        }


        // Users picking trays
        if (instant % TRAY_DELAY == 0) {
            // The desired amount of trays
            int desiredTraysAmount = getQueueSize(traysStation);
            Stack *usedTrays = createStack(desiredTraysAmount);

            // Remove the used trays from the stacks
            pickCellsfromStacks(usedTrays, trayStacks, TRAY_STACK_AMOUNT);

            // The amount of trays removed from the stacks
            int usedTraysAmount = getStackSize(usedTrays);

            // Remove users from traysStation
            spreadQueueOnQueues(traysStation, foodQueues,
                FOOD_QUEUE_AMOUNT, usedTraysAmount);

            // Add the next users from the tray queues to the trays station
            pickCellsfromQueues(traysStation, trayQueues, TRAY_QUEUE_AMOUNT);

            destroyStack(usedTrays, destroyTray);
        }

        // User picking food
        if (instant % FOOD_DELAY == 0) {
            int i;

            for(i = 0; i < FOOD_QUEUE_AMOUNT; i++) {
                if (isQueueFull(foodsStation[i])) {
                    Cell *finishedUserCell = popCellFromQueue(foodsStation[i]);

                    User *finishedUser = (User *) finishedUserCell->data;

                    finishedUser->finishedInstant = instant;

                    pushCellOnQueue(finishedUsers, finishedUserCell);
                }

                Queue *usersGoingToFoodStation = createQueue(FOOD_QUEUE_AMOUNT);
                pickCellsfromQueues(usersGoingToFoodStation, foodQueues,
                    FOOD_QUEUE_AMOUNT);
                spreadQueueOnQueues(usersGoingToFoodStation, foodsStation,
                    FOOD_QUEUE_AMOUNT, getQueueSize(usersGoingToFoodStation));
                destroyQueue(usersGoingToFoodStation, destroyUser);
            }
        }
    }

    printf("\n-- seed --\n");
    printSeed(seed);

    printf("\n-- checkoutQueues --\n");
    printQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, printUser);

    printf("\n-- checkout --\n");
    printQueue(checkout, printUser);

    printf("\n-- trayQueues --\n");
    printQueues(trayQueues, TRAY_QUEUE_AMOUNT, printUser);

    printf("\n-- traysStation --\n");
    printQueue(traysStation, printUser);

    printf("\n-- trayStacks --\n");
    printStacks(trayStacks, TRAY_STACK_AMOUNT, printTray);

    printf("\n-- foodQueues --\n");
    printQueues(foodQueues, FOOD_QUEUE_AMOUNT, printUser);

    printf("\n-- foodsStation --\n");
    printQueues(foodsStation, FOOD_QUEUE_AMOUNT, printUser);

    printf("\n-- finishedUsers --\n");
    printQueue(finishedUsers, printUser);

    printf("\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n");

    printf("\nTime user spent average: %.4f minutes\n",
        getTimeUserSpentAverage(&finishedUsers, timeStart));

    printf("\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n\n");

    destroySeed(seed);
    destroyQueue(checkout, destroyUser);
    destroyQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, destroyUser);
    destroyQueue(traysStation, destroyUser);
    destroyQueues(trayQueues, TRAY_QUEUE_AMOUNT, destroyUser);
    destroyStacks(trayStacks, TRAY_STACK_AMOUNT, destroyTray);
    destroyQueues(foodsStation, FOOD_QUEUE_AMOUNT, destroyUser);
    destroyQueues(foodQueues, FOOD_QUEUE_AMOUNT, destroyUser);
    destroyQueue(finishedUsers, destroyUser);

    return 0;
}