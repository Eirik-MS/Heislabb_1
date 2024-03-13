


typedef enum{
    STATIONARY,
    MOVEING_UP,
    MOVEING_DOWN,
    EMERGENCY_STOP
} direction_t;

typedef struct lift_state
{
    int current_floor;
    int last_floor;
    direction_t direction;
    direction_t prev_direction;

} lift_state_t;

extern lift_state_t lift_state;

// Initialize the lift state and corrects for starting between floors
void lift_state_init();

//returns true if state changes
int lift_state_update();
lift_state_t get_lift_state();
int set_lift_direction(direction_t direction);
