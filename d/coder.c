/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:27:45 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/07 12:15:49 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*coder_routine()      → thread function (main loop)*/
void *coder_routine(void *arg)
{
    t_coder *coder;
    coder = (t_coder *)arg;
    while (coder->data->flag_end == 0)
    {
        heap_arbiter_push(coder->data, coder);
        if (coder_compile(coder) == 0)
        {
            coder_debug(coder);
            coder_refactor(coder);
            
        }
    }
    return (NULL);
}
/*coder_compile()      → take dongles + compile + release*/
int coder_compile(t_coder *coder)
{
    if (coder_take_dongles(coder) != 0)
        return (1);
    heap_arbiter_pop(coder->data);
    coder->last_compile_time = get_time_ms();
    log_print(coder, "is compiling");
    usleep(coder->data->time_to_compile * 1000);
    dongle_release(coder->dongle_left, coder->data, 1);
    dongle_release(coder->dongle_right, coder->data, 1);
    coder->compile_count += 1;
    check_end(coder->data);
    pthread_cond_broadcast(&coder->data->arbiter->dongle_ready);
    return (0);
}
/*coder_debug()        → wait time_to_debug*/
void coder_debug(t_coder *coder)
{
    log_print(coder, "is debugging");
    usleep(coder->data->time_to_debug * 1000);
}

/*coder_refactor()     → wait time_to_refactor*/
void coder_refactor(t_coder *coder)
{
    log_print(coder, "is refactoring");
    usleep(coder->data->time_to_refactor * 1000);
}

/*log_print()          → print timestamp + coder state*/
void log_print(t_coder *coder, char *information)
{
    long timestamp;
    pthread_mutex_lock(&coder->data->mutex_print);
    if (coder->data->flag_end == 0)
    {
        timestamp = (get_time_ms()-(coder->data->start_time));
        printf("%ld %d %s\n", timestamp, coder->id, information);
    }
    pthread_mutex_unlock(&coder->data->mutex_print);
}
