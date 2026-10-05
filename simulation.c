/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:30:23 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 12:52:35 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*init_simulation()   → fills t_simulation with parsed args*/
void init_simulation(t_simulation *data)
{
    data->start_time = get_time_ms();
    data->flag_end = 0;
    pthread_mutex_init(&data->mutex_print, NULL);
}
/*init_coders()       → initializes the t_coder array
Coder 1 ── Dongle 0 ── Coder 2
   |                      |
Dongle 2              Dongle 1
   |                      |
Coder 3 ──────────────────
i=0 → (0+1) % 3 = 1  ✅
i=1 → (1+1) % 3 = 2  ✅
i=2 → (2+1) % 3 = 0  ✅ revient à 0 !
*/
int init_coders(t_simulation *data)
{
    int i;
    i = 0;
    data->coders = malloc(sizeof(t_coder) * data->number_of_coders);
    if (!data->coders)
        return(1);
    memset(data->coders, 0, sizeof(t_coder) * data->number_of_coders);
    while (i < data->number_of_coders)
    {
        data->coders[i].id = i + 1;
        data->coders[i].compile_count = 0;
        data->coders[i].last_compile_time = get_time_ms();
        data->coders[i].dongle_left = &data->dongles[i];
        data->coders[i].dongle_right = &data->dongles[(i + 1) % data->number_of_coders];
        data->coders[i].data = data;
        i++;
    }
    return (0);
}
/*init_dongles()      → initializes the t_dongle array
1 = free 0 = take
*/
int init_dongles(t_simulation *data)
{
    int i;
    i = 0;
    data->dongles = malloc(sizeof(t_dongle) * data->number_of_dongles);
    if(!data->dongles)
        return(1);
    memset(data->dongles, 0,sizeof(t_dongle) * data->number_of_dongles);
    while (i < data->number_of_dongles)
    {
        data->dongles[i].is_available = 1;
        dongle_init(&data->dongles[i], data, i);
        i++;
    }
    return (0);
}

/*init_arbiter()      → initializes t_arbiter*/
int init_arbiter(t_simulation *data)
{
    data->arbiter = malloc(sizeof(t_arbiter));
    if (!data->arbiter)
        return (1);
    data->arbiter->nodes = malloc(sizeof(t_coder *) * data->number_of_coders);
    if(!data->arbiter->nodes)
        return (1);
    memset(data->arbiter->nodes, 0, sizeof(t_coder *) * data->number_of_coders);
    data->arbiter->nb_coder_wait = 0;
    data->arbiter->scheduler = data->scheduler;
    pthread_cond_init(&data->arbiter->dongle_ready, NULL);
    pthread_mutex_init(&data->arbiter->mutex, NULL);
    return (0);
}
/*check_end()         → flag_end = 1 if burnout or all compiled*/
int check_end(t_simulation *data)
{
    int i;
    i = 0;
    while (i < data->number_of_coders)
    {
        if (data->coders[i].compile_count != data->number_of_compiles_required)
            return (0);
        i++;
    }
    data->flag_end = 1;
    return(1);
}
