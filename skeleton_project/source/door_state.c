#include "hardware.h"
#include "door_state.h"
#include "lift_state.h"

#include <stdio.h>


static door_state_t door_state;

void door_init(){
    door_state = door_open;
    hardware_command_door_open(1);
    if (hardware_read_obstruction_signal()){
        door_state= door_blocked;
    }
    else{
        door_state = door_closed;
        hardware_command_door_open(0);
    }  
    
}

void open_door(){
    if (lift_state_is_at_floor()){
        hardware_command_door_open(1);
    }
    else{
        printf("cannot open doors. Lift is in undifined state");
    }
}
void close_door(){
    if (!hardware_read_obstruction_signal()){
        hardware_command_door_open(0);
    }
    else{
        printf("cannot close doors. Door blocked");
    }
}

door_state_t get_door_state(){
    return door_state;
}