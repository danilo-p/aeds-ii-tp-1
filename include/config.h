#include <stdbool.h>

#ifndef CONFIG_H
#define CONFIG_H

/** Amount of checkout queues */
extern const int  CHECKOUT_QUEUE_AMOUNT;

/** Maximum size of the checkout queue */
extern const int  CHECKOUT_QUEUE_SIZE;

/** Time to the user be attended on the checkout */
extern const int  CHECKOUT_DELAY;

/** Amout of queues for taking a tray */
extern const int  TRAY_QUEUE_AMOUNT;

/** Maximum size of the tray queue */
extern const int  TRAY_QUEUE_SIZE;

/** Amount of tray stacks */
extern const int  TRAY_STACK_AMOUNT;

/** Maximum size of the stack tray */
extern const int  TRAY_STACK_SIZE;

/** Amount of trays that is inserted on the specified interval */
extern const int  TRAY_REFILL_AMOUNT;

/** Interval for creating new trays */
extern const int  TRAY_REFILL_INTERVAL;

/** Time to take a tray on the stack */
extern const int  TRAY_DELAY;

/** Amount of queues to take food */
extern const int  FOOD_QUEUE_AMOUNT;

/** Maximum size of the food queue */
extern const int  FOOD_QUEUE_SIZE;

/** Amount of options for taking food */
extern const int  FOOD_OPTIONS_AMOUNT;

/** Time for taking each food */
extern const int  FOOD_DELAY;

/** Interval for new users arrive */
extern const int  USER_ARRIVAL_INTERVAL;

/** Amount of users that arrive on each interval */
extern const int  USER_ARRIVAL_AMOUNT;

/** Total duration of the simulation */
extern const int  DURATION;

/** If enabled, show the final state of the simulation elements. */
extern const bool VERBOSE_RESULTS;

#endif