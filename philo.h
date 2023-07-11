/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:46:35 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/11 19:20:38 by Tanawat J.       ###   ########.fr       */
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

# define t_timeval struct timeval

enum e_status
{
	_think,
	_eat,
	_sleep,
	_dead
};

typedef struct s_rule
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int time_to_live;
	int	must_eat;
	int	eaten;
}	t_rule;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutx_fork;
	pthread_mutex_t	*mutx_table;
	struct s_philo	*right;
	struct s_philo	*left;
	enum e_status	status;
	int				id;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	mutx;
	t_rule			rules;
	int				len;
	int				halt;
	int				argc;
	int				*argv;
}				t_table;

#endif
