/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:29:56 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/15 13:08:06 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*monitor_routine()    → thread function (main loop)*/
void	*monitor_routine(void *arg)
{
	t_simulation	*data;

	data = (t_simulation *)arg;
	while (get_flag_end(data) == 0)
	{
		check_time_coders(data);
		heap_arbiter_wake(data);
		usleep(1000);
	}
	return (NULL);
}

/*check_time_coders()       → check each coder's last compile time*/
void	check_time_coders(t_simulation *data)
{
	int	i;

	i = 0;
	while (get_flag_end(data) == 0 && i < data->number_of_coders)
	{
		if (is_burned_out(data, i))
			return ;
		else
			i++;
	}
}

/*is_burned_out()      → returns 1 if time_to_burnout exceeded*/
int	is_burned_out(t_simulation *data, int i)
{
	long	last_compile;

	pthread_mutex_lock(&data->coders[i].mutex);
	last_compile = data->coders[i].last_compile_time;
	pthread_mutex_unlock(&data->coders[i].mutex);
	if (get_time_ms() - last_compile >= data->time_to_burnout)
	{
		log_print(&data->coders[i], "burned out");
		set_flag_end(data);
		return (1);
	}
	return (0);
}

/*get_flag_end()       → read flag_end under its mutex*/
int	get_flag_end(t_simulation *data)
{
	int	end;

	pthread_mutex_lock(&data->mutex_end);
	end = data->flag_end;
	pthread_mutex_unlock(&data->mutex_end);
	return (end);
}

/*set_flag_end()       → flag_end = 1 under its mutex + wake everybody*/
void	set_flag_end(t_simulation *data)
{
	pthread_mutex_lock(&data->mutex_end);
	data->flag_end = 1;
	pthread_mutex_unlock(&data->mutex_end);
	heap_arbiter_wake(data);
}
