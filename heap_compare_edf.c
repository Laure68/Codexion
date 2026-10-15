/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_compare_edf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 11:00:55 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/15 11:01:14 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	get_deadline(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->mutex);
	time = coder->last_compile_time;
	pthread_mutex_unlock(&coder->mutex);
	return (time);
}

static int	is_later(t_coder *a, t_coder *b)
{
	if (!b)
		return (1);
	if (get_deadline(a) != get_deadline(b))
		return (get_deadline(a) > get_deadline(b));
	return (a->id > b->id);
}

/*next_by_deadline()  → index of the next coder in deadline order
(oldest last_compile_time first), after "prev". prev = NULL → the first.*/
int	next_by_deadline(t_arbiter *arbiter, t_coder *prev)
{
	int	i;
	int	best;

	best = -1;
	i = 0;
	while (i < arbiter->nb_coder_wait)
	{
		if (is_later(arbiter->coder_queue[i], prev)
			&& (best == -1 || is_later(arbiter->coder_queue[best],
					arbiter->coder_queue[i])))
			best = i;
		i++;
	}
	return (best);
}

/*heap_compare_edf()  → same rule as fifo, but the order is the deadline.*/
int	heap_compare_edf(t_arbiter *arbiter)
{
	t_coder	*coder;
	int		i;

	clear_reserved(arbiter);
	coder = NULL;
	i = next_by_deadline(arbiter, coder);
	while (i >= 0)
	{
		coder = arbiter->coder_queue[i];
		if (!is_blocked(coder))
		{
			if (dongles_free(coder))
				return (i);
			reserve_dongles(coder);
		}
		i = next_by_deadline(arbiter, coder);
	}
	return (-1);
}
