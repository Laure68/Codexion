/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:29:41 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 10:31:48 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*main()               → orchestrator*/
int	main(int ac, char **av)
{
	t_simulation data;
    if (parse_args(ac, av, &data) != 0)
        return (1);
    if (init_simulation(&data) != 0)
        return (1);
    if (init_coders(&data) != 0)
        return (1);
    if (init_dongles(&data) != 0)
        return (1);
    if (init_arbiter(&data) != 0)
        return (1);
    if (launch_threads(&data) != 0)
        return (1);
    wait_finish_thread(&data);
    clean_simulation(&data);
    return (0);
}
/*launch_threads()     → creates coder threads + monitor*/
int launch_threads(t_simulation *data)
{
    pthread_t    *threads;
    int i;
    threads = malloc(sizeof(pthread_t) * data->number_of_coders);
    if (!threads)
        return (1);
    memset(threads, 0, sizeof(pthread_t) * data->number_of_coders);
    data->coders_threads = threads;
    i = 0;
    while (i < data->number_of_coders)
    {
        pthread_create(&threads[i], NULL, coder_routine, &data->coders[i]);
        i++;
    }
    pthread_create(&data->monitor_thread, NULL, monitor_routine, data);
    return (0); 
}
/*wait_finish_thread()       → waits for all threads to finish*/
int wait_finish_thread(t_simulation *data)
{
    pthread_t    *threads;
    int i;
    threads = data->coders_threads;
    i = 0;
    while (i < data->number_of_coders)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(data->monitor_thread, NULL);
    return (0); 
}
/*clean_simulation()   → frees memory*/
int clean_simulation(t_simulation *data)
{
    int i;
    heap_arbiter_free(data->arbiter, data);
    i = 0;
    while ((i < data->number_of_dongles))
    {
        dongle_destroy(&data->dongles[i]);
        i++;
    }
       pthread_mutex_destroy(&data->mutex_print);
    free(data->coders);
    free(data->dongles);
    free(data->coders_threads);
    return (0);
}
