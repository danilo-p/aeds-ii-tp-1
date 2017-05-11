#include "config.h"

// Amount of checkout queues
const int CHECKOUT_QUEUE_AMOUNT   = 1;

// Maximum size of the checkout queue
const int CHECKOUT_QUEUE_SIZE     = -1;

// Time to the user be attended on the checkout
const int CHECKOUT_DELAY          = 1;

// Amout of queues for taking a tray
const int TRAY_QUEUE_AMOUNT       = 1;

// Maximum size of the tray queue
const int TRAY_QUEUE_SIZE         = -1;

// Amount of tray stacks
const int TRAY_STACK_AMOUNT       = 1;

// Maximum size of the stack tray
const int TRAY_STACK_SIZE         = 40;

// Amount of trays that is inserted on the specified interval
const int TRAY_REFILL_AMOUNT      = 10;

// Interval for creating new trays
const int TRAY_REFILL_INTERVAL    = 12;

// Time to take a tray on the stack
const int TRAY_DELAY              = 1;

// Amount of queues to take food
const int FOOD_QUEUE_AMOUNT       = 1;

// Maximum size of the food queue
const int FOOD_QUEUE_SIZE         = -1;

// Amount of options for taking food
const int FOOD_OPTIONS_AMOUNT     = 4;

// Time for taking each food
const int FOOD_DELAY              = 1;

// Interval for new users arrive
const int USER_ARRIVAL_INTERVAL   = 1;

// Amount of users that arrive on each interval
const int USER_ARRIVAL_AMOUNT     = 2;

// Total duration of the simulation
const int DURATION                = 240;