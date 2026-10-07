/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:30:43 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 10:30:54 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*returns the actual time tv.tv_sec → sec tv.tv_usec → microsec*/
long get_time_ms(void)
{
    struct timeval    tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int heap_compare_fifo(t_arbiter *arbiter)
{
	if (arbiter->scheduler == FIFO)
		return (0);
	return (-1);
}

/*for heap_arbiter_compare()   */
int heap_compare_edf(t_arbiter *arbiter, t_simulation *data)
{
	long 	resting_time;
	long 	position1;
	long	min_resting_time;
	int 	i;
	int		indice_mini;
	i = 0;
	position1 = arbiter->coder_queue[i]->last_compile_time;
	resting_time = (data->time_to_burnout - (get_time_ms()- position1));
	min_resting_time = resting_time;
	indice_mini = 0;
	i = 1;
	while (i < arbiter->nb_coder_wait)
	{
		position1 = arbiter->coder_queue[i]->last_compile_time;
		resting_time = (data->time_to_burnout - (get_time_ms()- position1));
		if (resting_time < min_resting_time)
		{
			min_resting_time = resting_time;
			indice_mini = i;
		}
		i++;
	}
	return (indice_mini);
}
int coder_take_dongles(t_coder *coder)
{
    if (dongle_take(coder->dongle_right, coder) != 0)
    {
        heap_arbiter_pop(coder->data);
        return (1);
    }
        if (coder->dongle_left == coder->dongle_right)
    {
        while (coder->data->flag_end == 0)
            usleep(1000);
        heap_arbiter_pop(coder->data);
        dongle_release(coder->dongle_right, coder->data, 1);
        return (1);
    }
    if (dongle_take(coder->dongle_left, coder) != 0)
    {
        dongle_release(coder->dongle_right, coder->data, 1);
        heap_arbiter_pop(coder->data);
        return (1);
    }
    return (0);
}
int dongles_free(t_coder *coder)
{
    int right_ok;
    int left_ok;
    right_ok = 0;
    left_ok = 0;
    pthread_mutex_lock(&coder->dongle_right->mutex);
    if (coder->dongle_right->is_available == 1 
        && check_cooldown(coder->dongle_right) == 0)
        right_ok = 1;
    pthread_mutex_unlock(&coder->dongle_right->mutex);
    pthread_mutex_lock(&coder->dongle_left->mutex);
    if (coder->dongle_left->is_available == 1 
        && check_cooldown(coder->dongle_left) == 0)
        left_ok = 1;
    pthread_mutex_unlock(&coder->dongle_left->mutex);
    return (right_ok && left_ok);
}