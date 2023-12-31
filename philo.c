/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:07:27 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/13 22:13:03 by tjukmong         ###   ########.fr       */
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

void	death_signal(t_table *table, int i)
{
	destroy_mutx(table);
	printf("%-8ld %-3d died\n", ms_get_epoch()
		- table->philo[i].ms_begin, table->philo[i].id);
	i = -1;
	while (++i < table->len)
		table->philo[i].status = _dead;
	return ;
}

void	all_eaten(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->len)
		table->philo[i].status = _dead;
	usleep(15000);
	printf("-- All Philosophers has eaten %d time(s) --\n", table->argv[4]);
	return ;
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
				return (death_signal(table, i));
			nbr += table->philo[i].rules.eaten == table->philo[i]
				.rules.must_eat;
		}
		if (table->argc == 5 && nbr == table->len)
			return (all_eaten(table));
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
	usleep(1000);
	free_all(&table);
	return (0);
}
