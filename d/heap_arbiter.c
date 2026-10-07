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
    while (data->flag_end == 0
        && data->arbiter->coder_queue[heap_arbiter_compare(data->arbiter, 
        data)] != coder)
        pthread_cond_wait(&data->arbiter->dongle_ready, &data->arbiter->mutex);
    pthread_mutex_unlock(&data->arbiter->mutex);
}

/*heap_arbiter_pop()        → remove and return highest priority coder*/
t_coder *heap_arbiter_pop(t_simulation *data)
{
	int i;
    int k;
    t_coder *selected;
    pthread_mutex_lock(&data->arbiter->mutex);
    i = heap_arbiter_compare(data->arbiter, data);
    selected = data->arbiter->coder_queue[i];
    k = i;
    while (k < data->arbiter->nb_coder_wait - 1)
    {
        data->arbiter->coder_queue[k]= data->arbiter->coder_queue[k + 1];
        k++;
    }
    data->arbiter->nb_coder_wait -= 1;
    pthread_cond_broadcast(&data->arbiter->dongle_ready);
    pthread_mutex_unlock(&data->arbiter->mutex);
    return (selected);
}
/*heap_arbiter_free()       → destroy mutex + cond + free*/
int heap_arbiter_free(t_simulation *data)
{
    pthread_mutex_destroy(&data->arbiter->mutex);
    pthread_cond_destroy(&data->arbiter->dongle_ready);
    free(data->arbiter->coder_queue);
    free(data->arbiter);
    return (0);
}
/*heap_arbiter_compare()    → fifo / edf*/
int heap_arbiter_compare(t_arbiter *arbiter, t_simulation *data)
{
	if (arbiter->scheduler == FIFO)
		return (heap_compare_fifo(arbiter));
	if (arbiter->scheduler == EDF)
		return (heap_compare_edf(arbiter, data));
    return (0);

}

