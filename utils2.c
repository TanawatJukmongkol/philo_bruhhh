/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:17:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/14 04:04:40 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *ph, long time)
{
	if (pthread_mutex_lock(ph->mutx_table))
		return (1);
	if (time > ph->rules.time_to_live)
	{
		ph->status = _dead;
		pthread_mutex_unlock(ph->mutx_table);
		return (1);
	}
	pthread_mutex_unlock(ph->mutx_table);
	return (0);
}

void	ms_sleep(t_philo *ph, int ms)
{
	long	time;

	while (ph->status != _dead)
	{
		usleep(1);
		time = ms_get_epoch();
		if (check_die(ph, time) || time - ph->ms_now >= ms)
			break ;
	}
}
