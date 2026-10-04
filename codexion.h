#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h> 

typedef enum e_scheduler
{
    FIFO,
    EDF
}   t_scheduler;

typedef struct s_simulation
{
    int number_of_coders;
    int number_of_dongles;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    int number_of_compiles_required;
    long start_time;
    int flag_end;
    pthread_mutex_t mutex_print;
    t_coder *coders;
    t_dongle *dongles;
    t_arbiter *arbiter;
}   t_simulation;

typedef struct s_coder
{
    int id;
    int compile_count;
    long last_compile_time;
    t_dongle *dongle_left;
    t_dongle *dongle_right;
}   t_coder;

typedef struct s_dongle
{
    int id;
    pthread_mutex_t mutex;
    long last_released_time;
    long dongle_cooldown;
}   t_dongle;

typedef struct s_arbiter
{
    t_coder **nodes;
    int nb_coder_wait;
    t_scheduler scheduler;
    pthread_mutex_t mutex;
    phthread_cond_t dongle_ready;
}   t_arbiter;


/*coder*/


/*dungle*/

/*heap_arbiter*/


/*monitor*/

/*parser*/
int parse_args(int ac, char *av[], t_simulation *data);
int parse_args_data(char *av[], t_simulation *data);
int check_numbers(char *av[]);
int check_scheduler(char *av[]);
int check_coders(char *av[]);

/*simulation*/


#endif
