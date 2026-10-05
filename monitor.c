/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:29:56 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 12:50:02 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*monitor_routine()    → thread function (main loop)*/
void *monitor_routine(void *arg)
{
	t_simulation *data;
	data = (t_simulation *)arg;
	while (data->flag_end == 0)
	{
		check_coders(data);
		usleep(1000);
	}
	return (NULL);
}

/*check_coders()       → check each coder's last compile time*/
void check_coders(t_simulation *data)
{
	int i;
	i = 0;
	while (data->flag_end == 0 && i < data->number_of_coders)
	{
		if (is_burned_out(data, i))
			return ;
		else
			i++;
	}

}

/*is_burned_out()      → returns 1 if time_to_burnout exceeded*/
int is_burned_out(t_simulation *data, int i)
{
	if (get_time_ms()-
	data->coders[i].last_compile_time > data->time_to_burnout )
	{
		log_print(&data->coders[i], "burned out");
		data->flag_end = 1;
		return (1);
	}
	return (0);
}
