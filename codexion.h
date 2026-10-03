#ifndef CODEXION_H
# define CODEXION__H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

t_simulation
├── number_of_coders
├── number_of_dongles
├── time_to_burnout
├── time_to_compile
├── time_to_debug
├── time_to_refactor
├── number_of_compiles_required
├── start_time
├── flag_end
├── mutex_print
├── coders[]
├── dongles[]
└── arbiter (pointeur vers t_arbiter)

t_coder
├── id
├── compile_count
├── last_compile_time
├── dongle_left (pointeur vers t_dongle)
└── dongle_right (pointeur vers t_dongle)

t_dongle
├── id
├── mutex
├── cond
├── last_released_time
└── cooldown

t_arbiter
├── nodes[]
├── size
├── scheduler
├── mutex
└── cond
enum


/*coder*/


/*dungle*/

/*heap_arbiter*/


/*monitor*/

/*parser*/

/*simulation*/


#endif
