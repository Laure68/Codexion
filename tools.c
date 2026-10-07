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
int heap_compare_edf(t_simulation *data)
{
	long 	resting_time;
	long 	position1;
	long	min_resting_time;
	int 	i;
	int		indice_mini;
	i = 0;
	position1 = data->arbiter->coder_queue[i]->last_compile_time;
	resting_time = (data->time_to_burnout - (get_time_ms()- position1));
	min_resting_time = resting_time;
	indice_mini = 0;
	i = 1;
	while (i < data->arbiter->nb_coder_wait)
	{
		position1 = data->arbiter->coder_queue[i]->last_compile_time;
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
