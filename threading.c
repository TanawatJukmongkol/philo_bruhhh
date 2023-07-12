/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:00:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/12 19:21:23 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->ms_begin = ph->ms_begin + (ms_get_epoch() - ph->ms_begin); 
	while (1)
	{
		ph->ms_now = ms_get_epoch();
		// pthread_mutex_lock(ph->mutx_table);
		printf("%ld %d %s\n", ph->ms_now - ph->ms_begin, ph->id, "");
		// pthread_mutex_unlock(ph->mutx_table);
		ms_sleep(ph, 50);
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
		usleep(100);
		pthread_detach(table->philo[i].thread);
		i++;
	}
	return (0);
}
