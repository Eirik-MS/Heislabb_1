#include "hardware.h"
#include "channels.h"
#include "io.h"

#include <stdlib.h>

typedef enum{door_closed, door_open, door_blocked}door_state_t;

void door_init();

void open_door();
void close_door();
