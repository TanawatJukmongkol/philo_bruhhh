/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:07:27 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/13 11:21:12 by tjukmong         ###   ########.fr       */
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
	int		i;
	int		ac;
	int		*av;

	av = NULL;
	if (parse_args(argc, argv, &ac, &av) || init_data(&table, ac, av))
		return (1);
	spawn_philo(&table);
	while (1)
	{
		i = 0;
		while (i < table.len)
		{
			if (table.philo[i].status == _dead)
				exit(0);
			i++;
		}
		usleep(1);
	}
	free_all(&table);
	return (0);
}

