/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 11:39:50 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/09 11:42:45 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*coder_routine()      → thread function (main loop)*/
void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (get_flag_end(coder->data) == 0)
	{
		if (heap_arbiter_push(coder->data, coder) == 0
			&& coder_compile(coder) == 0)
		{
			coder_debug(coder);
			coder_refactor(coder);
		}
	}
	return (NULL);
}

/*coder_compile()      → take dongles + compile + release*/
int	coder_compile(t_coder *coder)
{
	if (coder->dongle_left == coder->dongle_right)
	{
		while (get_flag_end(coder->data) == 0)
			usleep(1000);
		dongle_release(coder->dongle_right, 0);
		return (1);
	}
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_time = get_time_ms();
	pthread_mutex_unlock(&coder->mutex);
	log_print(coder, "is compiling");
	usleep(coder->data->time_to_compile * 1000);
	dongle_release(coder->dongle_left, 1);
	dongle_release(coder->dongle_right, 1);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count += 1;
	pthread_mutex_unlock(&coder->mutex);
	check_end(coder->data);
	heap_arbiter_wake(coder->data);
	return (0);
}

/*coder_debug()        → wait time_to_debug*/
void	coder_debug(t_coder *coder)
{
	log_print(coder, "is debugging");
	usleep(coder->data->time_to_debug * 1000);
}

/*coder_refactor()     → wait time_to_refactor*/
void	coder_refactor(t_coder *coder)
{
	log_print(coder, "is refactoring");
	usleep(coder->data->time_to_refactor * 1000);
}

/*log_print()          → print timestamp + coder state*/
void	log_print(t_coder *coder, char *information)
{
	long	timestamp;

	pthread_mutex_lock(&coder->data->mutex_print);
	if (get_flag_end(coder->data) == 0)
	{
		timestamp = (get_time_ms() - (coder->data->start_time));
		printf("%ld %d %s\n", timestamp, coder->id, information);
	}
	pthread_mutex_unlock(&coder->data->mutex_print);
}
