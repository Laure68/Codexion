/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:27:45 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/06 08:37:19 by lmeny            ###   ########.fr       */
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
        heap_arbiter_push(coder);
        coder_compile(coder);
        coder_debug(coder);
        coder_refactor(coder);
    }
    return (NULL);
}
/*coder_compile()      → take dongles + compile + release*/
void coder_compile(t_coder *coder)
{
    if (dongle_take(coder->dongle_right, coder) != 0)
        return ;
    if (dongle_take(coder->dongle_left, coder) != 0)
    {
        dongle_release(coder->dongle_right, coder->data);
        return ;
    }
    log_print(coder, "is compiling");
    usleep(coder->data->time_to_compile * 1000);
    dongle_release(coder->dongle_left, coder->data);
    dongle_release(coder->dongle_right, coder->data);
    coder->compile_count += 1;
    pthread_cond_signal(&coder->data->arbiter->dongle_ready);
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
    timestamp = (get_time_ms()-(coder->data->start_time));
    printf("%ld %d %s\n", timestamp, coder->id, information);
    pthread_mutex_unlock(&coder->data->mutex_print);
}
