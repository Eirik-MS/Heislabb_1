
#include "lift_state.h"
#include "driver/elevio.h"
#include <stdbool.h>

static lift_state_t lift_state = {
    .current_floor = -1,
    .direction = STATIONARY
    //TODO: Emergency stop as own variable?
};

void lift_state_init(){
    if(elevio_floorSensor()==-1){
        while (elevio_floorSensor()==-1)
        {
            elevio_motorDirection(DIRN_UP);
        }
        elevio_motorDirection(DIRN_STOP);
        lift_state.current_floor=elevio_floorSensor();
        elevio_floorIndicator(lift_state.current_floor);
    }

    //TODO: See for the case when the elevator is above fourth floor
    //TODO: Fix case when the elevator starts with obstruction and between floors


    return;
}

void lift_state_update(){
    
    lift_state.current_floor = elevio_floorSensor();

    
}

bool lift_state_is_at_floor(){
    if(elevio_floorSensor != -1 && lift_state.direction == STATIONARY){
        return 1;
    }
    else{
        return 0;
    }      

}

lift_state_t get_lift_state(){
    return lift_state;
}

bool set_lift_direction(direction_t direction){
    switch (direction)
    {
    case MOVEING_UP:
        if(lift_state.current_floor==N_FLOORS-1){
            return 0;
        }
        else{
            elevio_motorDirection(DIRN_UP);
        }
        break;

    case MOVEING_DOWN:
        if(lift_state.current_floor==0){
            return 0;
        }
        else{
            elevio_motorDirection(DIRN_DOWN);
        }
    
    default:
        break;
    }



}