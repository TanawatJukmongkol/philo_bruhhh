/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:00:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/14 04:29:15 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	take_fork(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->mutx_fork))
		return (1);
	if (ph->fork_taken && ph->left->fork_taken)
	{
		pthread_mutex_unlock(&ph->mutx_fork);
		return (1);
	}
	if (!ph->left->fork_taken)
	{
		ph->left->fork_taken = 1;
	}
	if (!ph->fork_taken)
	{
		ph->fork_taken = 1;
		ph->status = _eat;
		if (ph->rules.eaten < ph->rules.must_eat)
			ph->rules.eaten++;
		pthread_mutex_unlock(&ph->mutx_fork);
		return (0);
	}
	pthread_mutex_unlock(&ph->mutx_fork);
	return (1);
}

void	release_fork(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->mutx_fork))
		return ;
	ph->fork_taken = 0;
	ph->left->fork_taken = 0;
	ph->status = _think;
	pthread_mutex_unlock(&ph->mutx_fork);
}

void	check_loop(t_philo *ph)
{
	while (ph->status != _dead)
	{
		if (ph->status == _think)
		{
			philo_log(ph, "is thinking");
			while (ph->status == _think)
				if (take_fork(ph))
					ms_sleep(ph, 0);
		}
		else if (ph->status == _eat)
		{
			philo_log(ph, "is eating");
			ph->rules.time_to_live = ph->ms_now + ph->rules.time_to_die;
			ph->status = _sleep;
			ms_sleep(ph, ph->rules.time_to_eat);
		}
		else if (ph->status == _sleep)
		{
			philo_log(ph, "is sleeping");
			release_fork(ph);
			ms_sleep(ph, ph->rules.time_to_sleep);
		}
	}
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->ms_now = ms_get_epoch();
	ph->rules.time_to_live = ph->ms_begin + ph->rules.time_to_die;
	if (ph->id % 2 == 0 && !ph->fork_taken)
		take_fork(ph);
	else
	{
		ph->status = _think;
		usleep(4999);
	}
	check_loop(ph);
	return (NULL);
}

int	spawn_philo(t_table *table)
{
	int	i;

	i = 0;
	table->ms_begin = ms_get_epoch();
	while (i < table->len)
	{
		table->philo[i].ms_begin = table->ms_begin;
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
