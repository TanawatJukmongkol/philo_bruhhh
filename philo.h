/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:46:35 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/13 18:13:35 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "lib/miniutils/miniutils.h"

# define PEDANTIC 0

typedef struct timeval	t_timeval;

enum e_status
{
	_think,
	_eat,
	_sleep,
	_dead
};

typedef struct s_rule
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	long	time_to_live;
	int		must_eat;
	int		eaten;
}	t_rule;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutx_fork;
	pthread_mutex_t	*mutx_table;
	struct s_philo	*right;
	struct s_philo	*left;
	enum e_status	status;
	t_rule			rules;
	long			ms_begin;
	long			ms_now;
	int				fork_taken;
	int				id;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	mutx;
	long			ms_begin;
	int				len;
	int				halt;
	int				argc;
	int				*argv;
}				t_table;

// utils
void	free_all(t_table *table);
int		init_each_data(t_table *table, int i, int argc, int *argv);
int		init_data(t_table *table, int argc, int *argv);
long	ms_get_epoch(void);
void	ms_sleep(t_philo *ph, int ms);

// message
void	philo_log(t_philo *ph, char *msg);
int		philo_error(t_table *table, char *msg);

// threading
void	*routine(void *philo);
int		spawn_philo(t_table *table);

#endif
