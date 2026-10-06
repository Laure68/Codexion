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

/*heap_arbiter_push()       → add coder to heap*/
void heap_arbiter_push(t_simulation *data, t_coder *coder)
{
	pthread_mutex_lock(&data->arbiter->mutex);
	data->arbiter->coder_queue[data->arbiter->nb_coder_wait] = coder;
	data->arbiter->nb_coder_wait += 1;
	pthread_mutex_unlock(&data->arbiter->mutex);
}

/*heap_arbiter_pop()        → remove and return highest priority coder*/
t_coder *heap_arbiter_pop(t_simulation *data, t_coder *coder)
{
	
}
/*heap_arbiter_free()       → destroy mutex + cond + free*/

/*heap_arbiter_compare()    → fifo / edf*/
int heap_arbiter_compare(t_arbiter *arbiter, t_simulation *data)
{
	if (arbiter->scheduler == FIFO)
		return (heap_compare_fifo(arbiter, data));
	if (arbiter->scheduler == EDF)
		return (heap_compare_edf(arbiter, data));

}

