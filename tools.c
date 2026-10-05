/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:30:43 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 10:30:54 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include codexion.h

/*returns the actual time tv.tv_sec → sec tv.tv_usec → microsec*/
long get_time_ms(void)
{
    struct timeval    tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
