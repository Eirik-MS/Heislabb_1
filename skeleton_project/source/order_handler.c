//Order handler for elevator orders
#include "order_handler.h"
#include "door_state.h"
#include "lift_state.h"
#include "driver/elevio.h"


void add_order_to_queue( order_t new){
    return;
}

void check_new_order(void){
    int btnPressed;
    order_t new;
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
            if(elevio_callButton(f, b)){
                elevio_buttonLamp(f, b, btnPressed);
                new.button = b;
                new.floor = f;
                add_order_to_queue(new);
            }
        }
    }
}