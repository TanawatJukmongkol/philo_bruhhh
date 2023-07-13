/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:07:27 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/13 19:43:00 by tjukmong         ###   ########.fr       */
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

void	main_routine(t_table *table)
{
	int	i;
	int	nbr;

	while (1)
	{
		i = -1;
		nbr = 0;
		usleep(1);
		while (++i < table->len)
		{
			if (table->philo[i].status == _dead)
			{
				philo_log(&table->philo[i], "died");
				i = -1;
				while (++i < table->len)
					table->philo[i].status = _dead;
				free_all(table);
				return ;
			}
			nbr += table->philo[i].rules.eaten == table->philo[i]
				.rules.must_eat;
		}
		i = -1;
		if (table->argc == 5 && nbr == table->len)
		{
			while (++i < table->len)
				table->philo[i].status = _dead;
			usleep(15000);
			printf("-- All Philosophers has eaten %d times --\n",
				table->argv[4]);
			return ;
		}
	}
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
	main_routine(&table);
	return (0);
}
