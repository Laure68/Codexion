











#include "codexion.h"

typedef struct s_coder
{
    int id;
    int compile_count;
    long last_compile_time;
    t_dongle *dongle_left;
    t_dongle *dongle_right;
    t_simulation *data;
}   t_coder;

/*coder_routine()      → thread function (main loop)*/
void *coder_routine(void *arg)
{
    t_coder *coder;
    coder = (t_coder *)arg;
    while (coder->data->flag_end == 0)
    {
        heap_arbiter_push(coder);
        coder_compile(coder);
        coder_debug(coder);
        coder_refactor(coder);
    }
    return (NULL);
}
/*coder_compile()      → take dongles + compile + release*/

/*coder_debug()        → wait time_to_debug*/

/*coder_refactor()     → wait time_to_refactor*/

/*log_print()          → print timestamp + coder state*/