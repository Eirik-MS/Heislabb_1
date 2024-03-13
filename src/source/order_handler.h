
#include "driver/elevio.h"

typedef struct order{
    int floor;
    ButtonType button;
} order_t;

void check_new_order(void);

void stop_if_order();

void handle_EM_stop();

void handle_movment();