

typedef enum {
    door_closed, 
    door_open, 
    door_blocked
} door_state_t;


void door_init();

void open_door();
int close_door();
door_state_t get_door_state();
void door_counter();