/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:00:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/12 23:08:31 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->ms_now = ms_get_epoch();
	while (ph->status != _dead)
	{
		philo_log(ph, "is thinking");
		ms_sleep(ph, 1000);
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
