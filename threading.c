/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:00:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/11 22:03:18 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->ms_begin = ms_get_epoch();
	while (1)
	{
		ph->ms_now = ms_get_epoch();
		printf("%ld %d %s\n", ph->ms_now - ph->ms_begin, ph->id, "");
		ms_sleep(ph, 1000);
	}
	return (NULL);
}

int	spawn_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->len)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				routine, &table->philo[i]))
		{
			free_all(table);
			return (1);
		}
		pthread_detach(table->philo[i].thread);
		usleep(10);
		i += 2;
		if (i >= table->len && i % 2 == 0)
			i = 1;
	}
	return (0);
}
