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
	int i;
    i = 0;
    while (i< arbiter->nb_coder_wait)
    {
        if (dongles_free(arbiter->coder_queue[i]))
		    return (i);
        i++;
    }
	return (-1);
}

/*for heap_arbiter_compare()   */
int heap_compare_edf(t_arbiter *arbiter)
{
	t_coder *current;
	int 	i;
	int		best_position;
	i = 0;
    best_position = -1;
	while (i < arbiter->nb_coder_wait)
	{
		current = arbiter->coder_queue[i];
        if (dongles_free(current) && (best_position == -1 
            || current->last_compile_time 
            < arbiter->coder_queue[best_position]->last_compile_time))
			best_position = i;
		i++;
	}
	return (best_position);
}
int coder_take_dongles(t_coder *coder)
{
    if (dongle_take(coder->dongle_right, coder) != 0)
        return (1);
    if (coder->dongle_left == coder->dongle_right)
        return (0);
    if (dongle_take(coder->dongle_left, coder) != 0)
    {
        dongle_release(coder->dongle_right, 0);
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