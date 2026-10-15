/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:30:43 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/15 12:21:39 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*returns the actual time tv.tv_sec → sec tv.tv_usec → microsec*/
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	coder_take_dongles(t_coder *coder)
{
	if (dongle_take(coder->dongle_right) != 0)
		return (1);
	if (coder->dongle_left == coder->dongle_right)
		return (0);
	if (dongle_take(coder->dongle_left) != 0)
	{
		dongle_release(coder->dongle_right, 0);
		return (1);
	}
	return (0);
}

int	dongles_free(t_coder *coder)
{
	int	right_ok;
	int	left_ok;

	right_ok = 0;
	left_ok = 0;
	pthread_mutex_lock(&coder->dongle_right->mutex);
	if (coder->dongle_right->is_available == 1
		&& check_cooldown(coder->dongle_right) == 0)
		right_ok = 1;
	pthread_mutex_unlock(&coder->dongle_right->mutex);
	pthread_mutex_lock(&coder->dongle_left->mutex);
	if (coder->dongle_left->is_available == 1
		&& check_cooldown(coder->dongle_left) == 0)
		left_ok = 1;
	pthread_mutex_unlock(&coder->dongle_left->mutex);
	return (right_ok && left_ok);
}

/*log_print()          → print timestamp + coder state*/
void	log_print_comp(t_coder *coder)
{
	long	timestamp;
	char	*take;
	char	*comp;

	take = "has taken a dongle";
	comp = "is compiling";
	if (check_end(coder->data) == 1)
		return ;
	pthread_mutex_lock(&coder->data->mutex_print);
	if (get_flag_end(coder->data) == 0)
	{
		timestamp = (get_time_ms() - (coder->data->start_time));
		printf("%ld %d %s\n", timestamp, coder->id, take);
		printf("%ld %d %s\n", timestamp, coder->id, take);
		printf("%ld %d %s\n", timestamp, coder->id, comp);
	}
	pthread_mutex_unlock(&coder->data->mutex_print);
}
