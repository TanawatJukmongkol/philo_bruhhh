/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:00:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/12 19:55:56 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(ph->mutx_table);
		ph->ms_now = ms_get_epoch();
		PRINT("is thinking");
		pthread_mutex_unlock(ph->mutx_table);
		ms_sleep(ph, 600);
	}
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
		{
			free_all(table);
			return (1);
		}
		usleep(5);
		pthread_detach(table->philo[i].thread);
		i += 2;
		if (i > table->len && i % 2 == 0)
			i = 1;
	}
	return (0);
}
