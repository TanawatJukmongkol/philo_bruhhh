/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:58:25 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/13 20:54:02 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutx(t_table *table)
{
	while (table->len)
	{
		pthread_mutex_destroy(&table->philo[table->len].mutx_fork);
		table->len--;
	}
	pthread_mutex_destroy(&table->mutx);
}

void	free_all(t_table *table)
{
	if (table->philo)
	{
		free(table->philo);
		table->philo = NULL;
	}
	if (table->argv)
		free(table->argv);
}

int	init_each_data(t_table *table, int i, int argc, int *argv)
{
	table->philo[i].id = i + 1;
	table->philo[i].mutx_table = &table->mutx;
	table->philo[i].fork_taken = 0;
	table->philo[i].rules.time_to_die = argv[1];
	table->philo[i].rules.time_to_eat = argv[2];
	table->philo[i].rules.time_to_sleep = argv[3];
	table->philo[i].rules.must_eat = -1;
	table->philo[i].rules.eaten = 0;
	if (argc == 5)
		table->philo[i].rules.must_eat = argv[4];
	if (pthread_mutex_init(&table->philo[i].mutx_fork, NULL))
		return (philo_error(table,
				"Failed to spawn philo: Failed to create mutex."));
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
	if (pthread_mutex_init(&table->mutx, NULL))
		return (1);
	table->len = argv[0];
	table->argc = argc;
	table->argv = argv;
	i = 0;
	while (i < argv[0])
	{
		if (init_each_data(table, i, argc, argv))
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

int	check_die(t_philo *ph, long time)
{
	if (pthread_mutex_lock(ph->mutx_table))
		return (1);
	if (time >= ph->rules.time_to_live)
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
