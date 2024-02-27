


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
