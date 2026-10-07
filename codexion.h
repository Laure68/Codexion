/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:27:12 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/06 10:59:45 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation t_simulation;
typedef struct s_coder t_coder; 

typedef enum e_scheduler
{
    FIFO,
    EDF
}   t_scheduler;

typedef struct s_dongle
{
    int id;
    int is_available;
    pthread_mutex_t mutex;
    long last_released_time;
    long dongle_cooldown;
}   t_dongle;

typedef struct s_arbiter
{
    t_coder **coder_queue;
    int nb_coder_wait;
    t_scheduler scheduler;
    pthread_mutex_t mutex;
    pthread_cond_t dongle_ready;
}   t_arbiter;

typedef struct s_coder
{
    int id;
    int compile_count;
    long last_compile_time;
    t_dongle *dongle_left;
    t_dongle *dongle_right;
    t_simulation *data;
}   t_coder;

typedef struct s_simulation
{
    int number_of_coders;
    int number_of_dongles;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long dongle_cooldown;
    int number_of_compiles_required;
    long start_time;
    int flag_end;
    pthread_mutex_t mutex_print;
    t_coder *coders;
    t_dongle *dongles;
    t_arbiter *arbiter;
    t_scheduler scheduler;
    pthread_t *coders_threads;
    pthread_t monitor_thread;
}   t_simulation;

/*coder*/
void *coder_routine(void *arg);
int coder_compile(t_coder *coder);
void coder_debug(t_coder *coder);
void coder_refactor(t_coder *coder);
void log_print(t_coder *coder, char *information);

/*dongle*/
void dongle_init(t_dongle *dongle, t_simulation *data, int index);
int dongle_take(t_dongle *dongle, t_coder *coder);
void dongle_release(t_dongle *dongle, t_simulation *data);
int check_cooldown(t_dongle *dongle);
void dongle_destroy(t_dongle *dongle);

/*heap_arbiter*/
void heap_arbiter_push(t_simulation *data, t_coder *coder);
t_coder *heap_arbiter_pop(t_simulation *data);
int heap_arbiter_free(t_simulation *data);
int heap_arbiter_compare(t_arbiter *arbiter, t_simulation *data);

/*main.c*/
int	main(int ac, char **av);
int launch_threads(t_simulation *data);
int wait_finish_thread(t_simulation *data);
int clean_simulation(t_simulation *data);

/*monitor*/
void *monitor_routine(void *arg);
void check_time_coders(t_simulation *data);
int is_burned_out(t_simulation *data, int i);

/*parser*/
int parse_args(int ac, char *av[], t_simulation *data);
int parse_args_data(char *av[], t_simulation *data);
int check_numbers(char *av[]);
int check_scheduler(char *av[]);
int check_coders(char *av[]);

/*simulation*/
int init_simulation(t_simulation *data);
int init_coders(t_simulation *data);
int init_dongles(t_simulation *data);
int init_arbiter(t_simulation *data);
int check_end(t_simulation *data);

/*tools*/
long get_time_ms(void);
int heap_compare_fifo(t_arbiter *arbiter);
int heap_compare_edf(t_simulation *data);

#endif
