/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 11:00:40 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/15 11:00:44 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_blocked(t_coder *coder)
{
	return (coder->dongle_left->reserved || coder->dongle_right->reserved);
}

void	reserve_dongles(t_coder *coder)
{
	coder->dongle_left->reserved = 1;
	coder->dongle_right->reserved = 1;
}

void	clear_reserved(t_arbiter *arbiter)
{
	int	i;

	i = 0;
	while (i < arbiter->nb_coder_wait)
	{
		arbiter->coder_queue[i]->dongle_left->reserved = 0;
		arbiter->coder_queue[i]->dongle_right->reserved = 0;
		i++;
	}
}

/*heap_compare_fifo()  → first coder in the queue that can take its dongles.
A coder who must wait reserves its 2 dongles: nobody behind him can use them.
A blocked coder does NOT reserve (no chain of waiting).*/
int	heap_compare_fifo(t_arbiter *arbiter)
{
	t_coder	*coder;
	int		i;

	clear_reserved(arbiter);
	i = 0;
	while (i < arbiter->nb_coder_wait)
	{
		coder = arbiter->coder_queue[i];
		if (!is_blocked(coder))
		{
			if (dongles_free(coder))
				return (i);
			reserve_dongles(coder);
		}
		i++;
	}
	return (-1);
}
