/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:28:36 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 11:49:19 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*dongle_init()        → initialize dongle + mutex*/
void dongle_init(t_dongle *dongle, t_simulation *data, int ind)
{
    dongle->id = ind;
    pthread_mutex_init(&dongle->mutex, NULL);
    dongle->dongle_cooldown = data->dongle_cooldown;
    dongle->last_released_time = 0;
}

/*dongle_take()        → lock + check availability + take*/
int dongle_take(t_dongle *dongle, t_coder *coder)
{
    pthread_mutex_lock(&dongle->mutex);
    if (check_cooldown(dongle)== 0)
    {
        dongle->is_available = 0;
        log_print(coder, "has taken a dongle");
    }
    else
    {
        pthread_mutex_unlock(&dongle->mutex);
        return (1);
    }
    pthread_mutex_unlock(&dongle->mutex);
    return (0);
}
/* dongle_release()     → release + start cooldown timer
is_available = 1 free // 0 = take
*/
void dongle_release(t_dongle *dongle, t_simulation *data)
{
    pthread_mutex_lock(&dongle->mutex);
    dongle->is_available = 1;
    dongle->last_released_time = get_time_ms();
    pthread_mutex_unlock(&dongle->mutex);
    pthread_cond_signal(&data->arbiter->dongle_ready);
}

/*check_cooldown()    → check if cooldown has passed*/
int check_cooldown(t_dongle *dongle)
{
    if (get_time_ms()- dongle->last_released_time >= dongle->dongle_cooldown)
        return (0);
    else
        return (1);

}

/*dongle_destroy()     → destroy mutex + free*/
void dongle_destroy(t_dongle *dongle)
{
    pthread_mutex_destroy(&dongle->mutex);
}
