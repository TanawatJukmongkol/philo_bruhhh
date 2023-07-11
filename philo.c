/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:07:27 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/11 16:57:45 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	parse_args(int argc, char**argv, int *ac, int **av)
{
	*av = argv_getint(ac, argv);
	if ((!*av && argc > 1) || (*ac > 0 && (*av[0] <= 0)))
	{
		printf("Invalid argument passed.\n");
		return (1);
	}
	if (*ac == 0)
	{
		free(*av);
		printf("No argument passed.\nUsage: ");
		printf("./philo nbr_philo time_to_live time_to_eat time_to_sleep\n");
		return (1);
	}
	if (*ac < 4 || *ac > 5)
	{
		printf("Too few / too much arguments.\n");
		free(*av);
		return (1);
	}
	return (0);
}

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

void	init_each_data(t_table *table, int i, int argc, int *argv)
{
	(void)(argc);
	table->philo[i].id = i + 1;
	if (i - 1 >= 0)
		table->philo[i].left = &table->philo[i - 1];
	else
		table->philo[i].left = &table->philo[argv[0] - 1];
	if (i + 1 < argv[0])
		table->philo[i].right = &table->philo[i + 1];
	else
		table->philo[i].right = &table->philo[0];
}

int	init_data(t_table *table, int argc, int *argv)
{
	int	i;

	table->len = 0;
	table->argv = NULL;
	table->philo = malloc(argv[0] * sizeof(t_philo));
	if (pthread_mutex_init(&table->mutx, NULL))
		return (1);
	i = -1;
	while (++i < argv[0])
	{
		if (pthread_mutex_init(&table->philo[i].mutx_fork, NULL))
		{
			free_all(table);
			return (1);
		}
		init_each_data(table, i, argc, argv);
	}
	table->len = argv[0];
	table->argc = argc;
	table->argv = argv;
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("%ld %d %s\n", (long)0, ph->id, "is spawning");
	return (NULL);
}

int	spawn_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->len)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				routine, table->philo))
		{
			free_all(table);
			return (1);
		}
		pthread_detach(table->philo[i].thread);
		i++;
	}
	return (0);
}

int	main(int argc, char**argv)
{
	t_table	table;
	int		ac;
	int		*av;

	av = NULL;
	if (parse_args(argc, argv, &ac, &av) || init_data(&table, ac, av))
		return (1);
	spawn_philo(&table);
	while (1)
		usleep(10);
	free_all(&table);
	return (0);
}

