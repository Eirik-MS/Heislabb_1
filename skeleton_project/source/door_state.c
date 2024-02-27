#include "hardware.h"
#include "channels.h"
#include "io.h"
#include "door_state.h"

#include <stdlib.h>

static enum door_state{
    door_closed,
    door_open,
    door_blocked

};

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
        print("cannot open doors. Lift is in undifined state");
    }
}
void close_door(){
    if (!hardware_read_obstruction_signal()){
        hardware_command_door_open(0);
    }
    else{
        print("cannot close doors. Door blocked");
    }
}

door_state get_door_state(){
    return door_state;
}