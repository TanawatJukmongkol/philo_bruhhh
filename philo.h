/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:46:35 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/11 16:46:40 by Tanawat J.       ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutx_fork;
	pthread_mutex_t	*mutx_table;
	struct s_philo	*right;
	struct s_philo	*left;
	int				id;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	mutx;
	int				len;
	int				argc;
	int				*argv;
}				t_table;

#endif
