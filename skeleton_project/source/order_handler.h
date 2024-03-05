
#include "driver/elevio.h"

typedef struct order{
    int floor;
    ButtonType button;
} order_t;

void check_new_order(void);

void add_order_to_queue(order_t new);