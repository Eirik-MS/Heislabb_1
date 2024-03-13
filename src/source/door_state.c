#include "driver/elevio.h"
#include "driver/con_load.h"
#include "door_state.h"
#include "time.h"




static door_state_t door_state;
static int Door_time_open;
static clock_t door_time_start;
static void door_start_counter();


void door_init(){
    door_state = door_open;
    elevio_doorOpenLamp(1);
    if (elevio_obstruction()){
        door_state= door_blocked;
    }
    else{
        door_state = door_closed;
        elevio_doorOpenLamp(0);
    }  
    
}

void open_door(){
        elevio_doorOpenLamp(1);
        door_state = door_open;
        door_start_counter();
        
    
}
int close_door(){
    if (!elevio_obstruction()){
        elevio_doorOpenLamp(0);
        door_state = door_closed;
        return 1;
    }
    else{
        return 0;
    }
    
}

door_state_t get_door_state(){
    return door_state;
}


void door_start_counter(){
    door_time_start = time(NULL);

}

void door_counter(){
    if (time(NULL) -door_time_start > 3){
        close_door();
    }
    if (elevio_obstruction()){
        door_state = door_blocked;
        door_start_counter();
    }
  
}