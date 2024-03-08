#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "order_handler.h"
#include "lift_state.h"
#include "door_state.h"



int main(){
    elevio_init();
    door_init();
    lift_state_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");


    while(1){
        check_new_order();
        lift_state_update();
        stop_if_order();
        //printf("=== Example Program ===\n");

        handle_movment();

        
        door_counter();
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            handle_EM_stop();
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
