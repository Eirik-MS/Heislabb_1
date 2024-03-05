
#include <stdbool.h>

typedef enum{
    STATIONARY,
    MOVEING_UP,
    MOVEING_DOWN,
    EMERGENCY_STOP
} direction_t;

typedef struct lift_state
{
    unsigned int current_floor;
    direction_t direction;

} lift_state_t;

// Initialize the lift state and corrects for starting between floors
void lift_state_init();
void lift_state_update();


void lift_state_update();


lift_state_t get_lift_state();


bool set_lift_direction(direction_t direction);


bool lift_state_is_at_floor();
