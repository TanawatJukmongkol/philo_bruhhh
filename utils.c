/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:58:25 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/12 19:42:25 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table)
{
	pthread_mutex_destroy(&table->mutx);
	while (table->len)
	{
		pthread_mutex_destroy(&table->philo[table->len].mutx_fork);
		table->len--;
	}
	if (table->philo)
		free(table->philo);
	if (table->argv)
		free(table->argv);
}

int	init_each_data(t_table *table, int i, int *argv)
{
	table->philo[i].mutx_table = &table->mutx;
	table->philo[i].ms_begin = &table->ms_begin;
	if (pthread_mutex_init(&table->philo[i].mutx_fork, NULL))
	{
		free_all(table);
		return (1);
	}
	table->philo[i].id = i + 1;
	if (i - 1 >= 0)
		table->philo[i].left = &table->philo[i - 1];
	else
		table->philo[i].left = &table->philo[argv[0] - 1];
	if (i + 1 < argv[0])
		table->philo[i].right = &table->philo[i + 1];
	else
		table->philo[i].right = &table->philo[0];
	return (0);
}

int	init_data(t_table *table, int argc, int *argv)
{
	int	i;

	table->len = 0;
	table->argv = NULL;
	table->philo = malloc(argv[0] * sizeof(t_philo));
	if (!table->philo || pthread_mutex_init(&table->mutx, NULL))
		return (1);
	table->len = argv[0];
	table->argc = argc;
	table->argv = argv;
	table->rules.time_to_die = argv[1];
	i = 0;
	while (i < argv[0])
	{
		if (init_each_data(table, i, argv))
			return (1);
		i++;
	}
	return (0);
}

long	ms_get_epoch(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ms_sleep(t_philo *ph, int ms)
{
	while (1)
	{
		usleep(10);
		if (ms_get_epoch() - ph->ms_now >= ms)
			break ;
	}
}
