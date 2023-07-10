/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:46:35 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/10 22:49:21 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEBUG_MODE 0

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "lib/miniutils/miniutils.h"

typedef struct s_philo
{
	pthread_mutex_t	mutx_fork;
	pthread_mutex_t	*mutx_table;
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
