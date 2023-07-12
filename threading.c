/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:00:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/13 01:21:41 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->ms_now = ms_get_epoch();
	if (ph->id % 2 && !ph->fork_taken)
	{
		ph->fork_taken = 1;
		ph->left->fork_taken = 1;
		ph->status = _eat;
	}
	else
		ph->status = _think;
	while (ph->status != _dead)
	{
		if (ph->status == _think)
		{
			philo_log(ph, "is thinking");
			while (ph->status == _think)
			{
				pthread_mutex_lock(&ph->mutx_fork);
				if (!ph->fork_taken && !ph->left->fork_taken)
				{
					ph->fork_taken = 1;
					ph->left->fork_taken = 1;
					ph->status = _eat;
					pthread_mutex_unlock(&ph->mutx_fork);
					break ;
				}
				else
					ms_sleep(ph, 5);
				pthread_mutex_unlock(&ph->mutx_fork);
			}
		}
		else if (ph->status == _eat)
		{
			philo_log(ph, "is eating");
			ph->rules.time_to_live = ph->rules.time_to_die;
			ms_sleep(ph, ph->rules.time_to_eat);
			ph->status = _sleep;
		}
		else if (ph->status == _sleep)
		{
			philo_log(ph, "is sleeping");
			pthread_mutex_lock(&ph->mutx_fork);
			ph->fork_taken = 0;
			ph->left->fork_taken = 0;
			pthread_mutex_unlock(&ph->mutx_fork);
			ms_sleep(ph, ph->rules.time_to_sleep);
			ph->status = _think;
		}
	}
	philo_log(ph, "died");
	return (NULL);
}

int	spawn_philo(t_table *table)
{
	int	i;

	i = 0;
	table->ms_begin = ms_get_epoch();
	while (i < table->len)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				routine, &table->philo[i]))
			return (philo_error(table,
					"Failed to spawn philo: Failed to create thread."));
		usleep(5);
		pthread_detach(table->philo[i].thread);
		i += 2;
		if (i >= table->len && i % 2 == 0)
			i = 1;
	}
	return (0);
}
