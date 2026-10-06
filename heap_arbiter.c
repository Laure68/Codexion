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

/*heap_arbiter_pop()        → remove and return highest priority coder
1. appeler heap_arbiter_compare() pour avoir l'index du prioritaire
2. sauvegarder le coder à cet index
3. supprimer ce coder de la queue
4. décrémenter nb_coder_wait
5. retourner le coder sauvegardé*/

t_coder *heap_arbiter_pop(t_simulation *data)
{
	int i;
    int last;
    t_coder *selected;
    pthread_mutex_lock(&data->arbiter->mutex);
    i = heap_arbiter_compare(data->arbiter, data);
    last = data->arbiter->nb_coder_wait -1;
    selected = data->arbiter->coder_queue[i];
    data->arbiter->coder_queue[i]= data->arbiter->coder_queue[last];
    data->arbiter->nb_coder_wait -= 1; 
    pthread_mutex_unlock(&data->arbiter->mutex);
    return (selected);
}
/*heap_arbiter_free()       → destroy mutex + cond + free*/
int heap_arbiter_free(t_arbiter *arbiter, t_simulation *data)
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
		return (heap_compare_fifo(arbiter, data));
	if (arbiter->scheduler == EDF)
		return (heap_compare_edf(arbiter, data));

}

