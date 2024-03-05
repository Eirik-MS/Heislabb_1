//Order handler for elevator orders
#include "order_handler.h"
#include "door_state.h"
#include "lift_state.h"
#include "driver/elevio.h"

#include <stdio.h>
#include <stdlib.h>

int queue_size = 0;

order_t * order_queue;

//TODO: Add dynamic memmory
void add_order_to_queue(order_t new){
    if (queue_size>0){
        //Check if identical order exists
        for(int i= 0; i<queue_size; i++){
            if(order_queue[i].floor == new.floor &&
               order_queue[i].button == new.button){
                return;
               }
        }
    }else{
        order_queue[0].floor = new.floor;
        order_queue[0].button = new.button;
    }
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