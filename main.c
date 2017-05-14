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
 * @return     0
 */
int main() {
    /*===================================================
    =            Initializing the simulation            =
    ===================================================*/

    /**
     * The timeStart stores the moment that the simulation will start.
     */
    int timeStart = 0;
    /*
     * The infinityADT is used to create ADT with no maximum length specified.
     */
    int infinityADT = -1;
    /**
     * The instant is used to store the time in minutes of the simulation. Its
     * initial value is the timeStart value. Its final value is the DURATION
     * constant specified on the configuration header.
     */
    int instant;

    /**
     * The seed used to generate all the unique identifiers of the program. More
     * specifically, it is used to generate the trays and the users ids.
     */
    Seed *seed = createSeed(timeStart);

    /**
     * The checkoutQueues stores all the queues that users will wait for being
     * attended.
     */
    Queue *checkoutQueues[CHECKOUT_QUEUE_AMOUNT];
    createQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, CHECKOUT_QUEUE_SIZE);

    /**
     * The checkout that the users will be attended.
     *
     * The choice of the ADT Queue was arbitrary. It was used because makes easy
     * to manipulate the changes between users going to the trayQueues.
     */
    Queue *checkout = createQueue(CHECKOUT_QUEUE_AMOUNT);

    /**
     * The trayQueues stores all the queues that the users will wait to pick a
     * tray on the trays stacks.
     */
    Queue *trayQueues[TRAY_QUEUE_AMOUNT];
    createQueues(trayQueues, TRAY_QUEUE_AMOUNT, TRAY_QUEUE_SIZE);

    /**
     * The traysStation is the place that the users will pick a tray on the tray
     * stacks or wait, if there is no tray to catch.
     */
    Queue *traysStation = createQueue(TRAY_STACK_AMOUNT);

    /**
     * The trayStacks is used to store the trays that the users will "use".
     * Actually, the trays will just be destroyed once the users pop them from
     * the stacks.
     */
    Stack *trayStacks[TRAY_STACK_AMOUNT];
    createStacks(trayStacks, TRAY_STACK_AMOUNT, TRAY_STACK_SIZE);

    /**
     * The foodQueues stores all the queues that the users will wait for picking
     * food.
     */
    Queue *foodQueues[FOOD_QUEUE_AMOUNT];
    createQueues(foodQueues, FOOD_QUEUE_AMOUNT, FOOD_QUEUE_SIZE);

    /**
     * The foodsStation is the place that the users will be picking food.
     */
    Queue *foodsStation[FOOD_QUEUE_AMOUNT];
    createQueues(foodsStation, FOOD_QUEUE_AMOUNT, FOOD_OPTIONS_AMOUNT);


    /**
     * The finishedUsers is the queue that all the users that is done with the
     * restaurant services will be. On the finish of the program it will be used
     * to calculate the average time that a user spents on the restaurant.
     */
    Queue *finishedUsers = createQueue(infinityADT);

    /*=====  End of Initializing the simulation  ======*/

    /*==================================
    =            Simulation            =
    ==================================*/

    for(instant = timeStart; instant < DURATION; instant++) {
        /* The users arrival. */
        if (instant % USER_ARRIVAL_INTERVAL == 0) {
            insertNewUsers(checkoutQueues, CHECKOUT_QUEUE_AMOUNT,
                USER_ARRIVAL_AMOUNT, instant, seed);
        }

        /* The trays being placed at the stacks. */
        if (instant % TRAY_REFILL_INTERVAL == 0) {
            insertNewTrays(trayStacks, TRAY_STACK_AMOUNT,
                TRAY_REFILL_AMOUNT * TRAY_STACK_AMOUNT, instant, seed);
        }

        /* The checkout service. */
        if (instant % CHECKOUT_DELAY == 0) {
            /* Remove users that were attended from the checkout. */
            spreadQueueOnQueues(checkout, trayQueues, TRAY_QUEUE_AMOUNT,
                getQueueSize(checkout));

            /* Add the next users of the queues on the checkout. */
            pickCellsfromQueues(checkout, checkoutQueues,
                CHECKOUT_QUEUE_AMOUNT);
        }

        /* The users picking trays from the stack. */
        if (instant % TRAY_DELAY == 0) {
            /* The desired amount of trays is the amount of users that will pick
             * trays. */
            int desiredTraysAmount = getQueueSize(traysStation);
            Stack *usedTrays = createStack(desiredTraysAmount);

            /* Remove the trays from the stacks. */
            pickCellsfromStacks(usedTrays, trayStacks, TRAY_STACK_AMOUNT);

            /*
             * The amount of trays removed from the stacks. It can be different
             * from the desired amount, because the stacks can be empty or the
             * amount of trays can be lower than the needed amount.
             */ 
            int usedTraysAmount = getStackSize(usedTrays);

            /* Remove usedTraysAmount amount of users from traysStation. */
            spreadQueueOnQueues(traysStation, foodQueues,
                FOOD_QUEUE_AMOUNT, usedTraysAmount);

            /*
             * Add the next users from the tray queues to the trays station.
             * Remaining users that were not attended will be in front of the
             * new users.
             */
            pickCellsfromQueues(traysStation, trayQueues, TRAY_QUEUE_AMOUNT);

            /* Destroys the auxiliar stack usedTrays. */
            destroyStack(usedTrays, destroyTray);
        }

        /* Users picking food */
        if (instant % FOOD_DELAY == 0) {
            int i;

            /*
             * Here its needed to check queue per queue if it is full. If is the
             * case, the first user of the queue is done.
             */
            for(i = 0; i < FOOD_QUEUE_AMOUNT; i++) {
                if (isQueueFull(foodsStation[i])) {
                    Cell *finishedUserCell = popCellFromQueue(foodsStation[i]);

                    User *finishedUser = (User *) finishedUserCell->data;

                    finishedUser->finishedInstant = instant;

                    pushCellOnQueue(finishedUsers, finishedUserCell);
                }
            }

            /*
             * Move the next users from the foodQueues to the foodsStations.
             */
            Queue *usersGoingToFoodStation = createQueue(FOOD_QUEUE_AMOUNT);
            pickCellsfromQueues(usersGoingToFoodStation, foodQueues,
                FOOD_QUEUE_AMOUNT);
            spreadQueueOnQueues(usersGoingToFoodStation, foodsStation,
                FOOD_QUEUE_AMOUNT, getQueueSize(usersGoingToFoodStation));
            destroyQueue(usersGoingToFoodStation, destroyUser);
        }
    }

    /*=====  End of Simulation  ======*/

    /*=====================================================
    =            Presenting Simulation Results            =
    =====================================================*/

    if (VERBOSE_RESULTS) {
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
    }

    printf("\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n");

    printf("\nTime user spent average: %.4f minutes\n",
        getTimeUserSpentAverage(&finishedUsers, timeStart));

    printf("\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n\n");

    /*=====  End of Presenting Simulation Results  ======*/

    /*=============================================
    =            Finalizing Simulation            =
    =============================================*/

    destroySeed(seed);
    destroyQueue(checkout, destroyUser);
    destroyQueues(checkoutQueues, CHECKOUT_QUEUE_AMOUNT, destroyUser);
    destroyQueue(traysStation, destroyUser);
    destroyQueues(trayQueues, TRAY_QUEUE_AMOUNT, destroyUser);
    destroyStacks(trayStacks, TRAY_STACK_AMOUNT, destroyTray);
    destroyQueues(foodsStation, FOOD_QUEUE_AMOUNT, destroyUser);
    destroyQueues(foodQueues, FOOD_QUEUE_AMOUNT, destroyUser);
    destroyQueue(finishedUsers, destroyUser);

    /*=====  End of Finalizing Simulation  ======*/

    return 0;
}