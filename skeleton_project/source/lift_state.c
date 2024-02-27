
#include "lift_state.h"
#include "hardware.h"
#include <stdbool.h>

static lift_state_t lift_state = {
    .current_floor = -1,
    .direction = STATIONARY
    //TODO: Emergency stop as own variable?
};

void lift_state_init(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            lift_state.current_floor = i;
        }
    }
    //TODO: See for the case when the elevator is above fourth floor
    //TODO: Fix case when the elevator starts with obstruction and between floors

    if (lift_state.current_floor == -1){ 
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        lift_state.direction = MOVEING_UP;
        while (lift_state.current_floor == -1){
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
                hardware_read_floor_sensor(i) ? lift_state.current_floor = i : -1;
            }
        }
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    }

    hardware_command_floor_indicator_on(lift_state.current_floor);

    return;
}

void lift_state_update(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if (hardware_read_floor_sensor(i)){
            lift_state.current_floor = i;
        }
    }
    return;
}

bool lift_state_is_at_floor(){
    if (lift_state.direction == STATIONARY && lift_state.current_floor != -1){
        return true;
    }
}

lift_state_t get_lift_state(){
    return lift_state;
}

bool set_lift_direction(direction_t direction){
    switch (direction)
    {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }
}