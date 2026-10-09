/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_arbiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:29:17 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 10:29:22 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*heap_arbiter_push()       → add coder to the queue, wait until the arbiter
chooses it (first servable coder), take its dongles, remove it from the queue
returns 0 = dongles taken, 1 = simulation ended*/
int	heap_arbiter_push(t_simulation *data, t_coder *coder)
{
	t_arbiter	*arbiter;
	int			i;
	int			res;

	arbiter = data->arbiter;
	res = 1;
	pthread_mutex_lock(&arbiter->mutex);
	arbiter->coder_queue[arbiter->nb_coder_wait] = coder;
	arbiter->nb_coder_wait += 1;
	while (get_flag_end(data) == 0 && res == 1)
	{
		i = heap_arbiter_compare(arbiter);
		if (i >= 0 && arbiter->coder_queue[i] == coder
			&& coder_take_dongles(coder) == 0)
		{
			heap_arbiter_pop(arbiter, i);
			res = 0;
		}
		else
			pthread_cond_wait(&arbiter->dongle_ready, &arbiter->mutex);
	}
	pthread_mutex_unlock(&data->arbiter->mutex);
	return (res);
}

/*heap_arbiter_pop()        → remove and return the coder at index i */
t_coder	*heap_arbiter_pop(t_arbiter *arbiter, int i)
{
	t_coder	*selected;

	selected = arbiter->coder_queue[i];
	while (i < arbiter->nb_coder_wait - 1)
	{
		arbiter->coder_queue[i] = arbiter->coder_queue[i + 1];
		i++;
	}
	arbiter->nb_coder_wait -= 1;
	return (selected);
}

/*heap_arbiter_wake()       → wake every waiting coder (mutex held)*/
void	heap_arbiter_wake(t_simulation *data)
{
	pthread_mutex_lock(&data->arbiter->mutex);
	pthread_cond_broadcast(&data->arbiter->dongle_ready);
	pthread_mutex_unlock(&data->arbiter->mutex);
}

/*heap_arbiter_free()       → destroy mutex + cond + free*/
int	heap_arbiter_free(t_simulation *data)
{
	pthread_mutex_destroy(&data->arbiter->mutex);
	pthread_cond_destroy(&data->arbiter->dongle_ready);
	free(data->arbiter->coder_queue);
	free(data->arbiter);
	return (0);
}

/*heap_arbiter_compare()    → returns fifo / edf*/
int	heap_arbiter_compare(t_arbiter *arbiter)
{
	if (arbiter->scheduler == EDF)
		return (heap_compare_edf(arbiter));
	return (heap_compare_fifo(arbiter));
}
