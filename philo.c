/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:07:27 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/10 22:52:53 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (table->argv)
		free(table->argv);
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
		table->philo[i].id = i + 1;
		if (pthread_mutex_init(&table->philo[i].mutx_fork, NULL))
		{
			free_all(table);
			return (1);
		}
	}
	table->len = argv[0];
	table->argc = argc;
	table->argv = argv;
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
	free_all(&table);
	return (0);
}
