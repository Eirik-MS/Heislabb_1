#include "door_state.h"
#include "lift_state.h"
#include "driver/elevio.h"
#include <stdbool.h>

lift_state_t lift_state = {
    .current_floor = -1,
    .direction = STATIONARY,
    .last_floor = -1,
    .prev_direction = STATIONARY
    //TODO: Emergency stop as own variable?
};


void lift_state_init(){
    for (int i = 0; i< N_FLOORS; i++){
        for (int j =0; j<N_BUTTONS;j++){
            elevio_buttonLamp(i, j, 0);
        }
    }

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

int lift_state_update(){
    
    lift_state.current_floor = elevio_floorSensor();
    //printf("===Lift state update===\nCurrent floor: %d\n", lift_state.current_floor);
    //printf("Last floor: %d\n", lift_state.last_floor);
    if (lift_state.current_floor != lift_state.last_floor){
        if (lift_state.current_floor != -1){
            elevio_floorIndicator(lift_state.current_floor);
            lift_state.last_floor = lift_state.current_floor;
        }
        
        return 1;
    }
    if (lift_state.current_floor != -1){
        elevio_floorIndicator(lift_state.current_floor);
        lift_state.last_floor = lift_state.current_floor;
        //return 1;
    }
    return 0;
}

bool lift_state_is_at_floor(){
    if(elevio_floorSensor() != -1 && lift_state.direction == STATIONARY){
        return 1;
    }
    else{
        return 0;
    }      

}

lift_state_t get_lift_state(){
    return lift_state;
}

int set_lift_direction(direction_t direction){
    if(get_door_state()==door_closed){
        switch (direction)
        {
        case MOVEING_UP:
            if(lift_state.current_floor==N_FLOORS-1){
                return 0;
            }
            else{
                lift_state.prev_direction = lift_state.direction;
                lift_state.direction = MOVEING_UP;
                elevio_motorDirection(DIRN_UP);
                return 1;
            }
            break;

        case MOVEING_DOWN:
            if(lift_state.current_floor==0){
                return 0;
            }
            else{
                lift_state.prev_direction = lift_state.direction;
                lift_state.direction = MOVEING_DOWN;
                elevio_motorDirection(DIRN_DOWN);
                return 1;
            }
            break;

        case STATIONARY:
            lift_state.prev_direction = lift_state.direction;
            lift_state.direction = STATIONARY;
            elevio_motorDirection(DIRN_STOP);
            return 1;
            break;

        case EMERGENCY_STOP:
            lift_state.prev_direction = lift_state.direction;
            lift_state.direction = EMERGENCY_STOP;
            elevio_motorDirection(DIRN_STOP);
            return 1;
            break;
        }
    } else {
        switch (direction)
        {
        case STATIONARY:
            lift_state.prev_direction = lift_state.direction;
            lift_state.direction = STATIONARY;
            elevio_motorDirection(DIRN_STOP);
            return 1;
            break;

        case EMERGENCY_STOP:
            lift_state.prev_direction = lift_state.direction;
            lift_state.direction = EMERGENCY_STOP;
            elevio_motorDirection(DIRN_STOP);
            return 1;
            break;
        default:
            return 0;
        }
    }
    return 0;
}