/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:07:27 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/11 21:56:23 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>

int	parse_args(int argc, char**argv, int *ac, int **av)
{
	*av = argv_getint(ac, argv);
	if ((!*av && argc > 1) || (*ac > 0 && (*av[0] <= 0)))
	{
		free(*av);
		printf("Invalid argument passed.\n");
		return (1);
	}
	if (*ac == 0)
	{
		free(*av);
		printf("No argument passed.\nUsage: ./philo ");
		printf("nbr_philo time_to_live time_to_eat time_to_sleep must_eat\n");
		return (1);
	}
	if (*ac < 4 || *ac > 5)
	{
		free(*av);
		printf("Too few / too much arguments.\n");
		return (1);
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
	{
		// if (table.halt == 1)
		// 	printf("Philosopher xx died.\n");
		// else if (table.halt == 2)
		// 	printf("All philosopher has eaten.\n");
		usleep(10);
	}
	free_all(&table);
	return (0);
}

