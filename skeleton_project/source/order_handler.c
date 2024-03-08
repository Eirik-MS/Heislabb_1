//Order handler for elevator orders
#include "order_handler.h"
#include "door_state.h"
#include "lift_state.h"
#include "driver/elevio.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int queue_size = 0;

order_t order_queue[20];

static void add_order_to_queue(order_t new);
static void remove_order(int index);

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
        order_queue[queue_size].floor = new.floor;
        order_queue[queue_size].button = new.button;
        queue_size++;
    }else{
        order_queue[0].floor = new.floor;
        order_queue[0].button = new.button;
        queue_size++;
    }
}

void handle_movment(){
    
    if( queue_size > 0 && 
        lift_state.direction == STATIONARY){
        printf("NORMAL: Queue size: %d\n", queue_size);
        if (order_queue[0].floor > lift_state.current_floor)
        {
            set_lift_direction(MOVEING_UP);
        } else {
            set_lift_direction(MOVEING_DOWN);
        }
    
    } else if(queue_size > 0 && lift_state.direction == EMERGENCY_STOP){
        //Handle stop from EM
        if (lift_state.current_floor == -1){
            printf("EMERGENCY: Last Floor: %d", lift_state.last_floor);
            if (order_queue[0].floor > lift_state.last_floor && 
                lift_state.prev_direction == MOVEING_UP){
                set_lift_direction(MOVEING_UP);
            } else {

                set_lift_direction(MOVEING_DOWN);
            }
        } else {
            printf("EMERGENCY: Last Floor: %d", lift_state.last_floor);
            if (order_queue[0].floor > lift_state.current_floor){
                set_lift_direction(MOVEING_UP);
            } else {
                set_lift_direction(MOVEING_DOWN);
            }
        }
        return;
    }
}


void check_new_order(void){
    int btnPressed;
    order_t new;
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            //btnPressed = elevio_callButton(f, b);
            //elevio_buttonLamp(f, b, btnPressed);
            if(elevio_callButton(f, b)){
                elevio_buttonLamp(f, b, 1);
                new.button = b;
                new.floor = f;
                add_order_to_queue(new);
            }
        }
    }
}

void stop_if_order(){
    for(int i=0; i<queue_size; i++){

        if(order_queue[i].floor==lift_state.current_floor){
            printf("STOP: Floor: %d\n", order_queue[i].floor);
            switch (order_queue[i].button)
            {
            case BUTTON_CAB:
                set_lift_direction(STATIONARY);
                open_door();
                elevio_buttonLamp(order_queue[i].floor, BUTTON_CAB, 0);
                remove_order(i);
                i--;
                break;

            case BUTTON_HALL_DOWN:
                if(lift_state.direction==MOVEING_DOWN){
                    set_lift_direction(STATIONARY);
                    open_door();
                    elevio_buttonLamp(order_queue[i].floor, BUTTON_HALL_DOWN, 0);
                    remove_order(i);
                    i--;
                }
                break;

            case BUTTON_HALL_UP:
                if(lift_state.direction==MOVEING_UP){
                    set_lift_direction(STATIONARY);
                    open_door();
                    elevio_buttonLamp(order_queue[i].floor, BUTTON_HALL_UP, 0);
                    remove_order(i);
                } else if (order_queue[i].floor == 0){
                    set_lift_direction(STATIONARY);
                    open_door();
                    elevio_buttonLamp(order_queue[i].floor, BUTTON_HALL_UP, 0);
                    remove_order(i);
                    i--;
                }
                break;
        
            
            default:
                break;
            }
        }
    }
}

void remove_order(int index){
    for(int i=index; i<queue_size; i++){
    order_queue[i]=order_queue[i+1];
    }
    order_queue[queue_size-1].floor=-1;
    queue_size --;
}

void handle_EM_stop(){
    printf("EMERGENCY STOP\n");
    set_lift_direction(EMERGENCY_STOP);
    printf("Floor: %d\n", lift_state.current_floor);
    while(elevio_stopButton()){
        elevio_stopLamp(1);
    }
    elevio_stopLamp(0);
    //Empty queue
    for (int i = 0; i < queue_size; i++){
        elevio_buttonLamp(order_queue[i].floor, order_queue[i].button, 0);
        order_queue[i].floor = -1;
    }
    queue_size = 0;
}