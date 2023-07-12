/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:18:36 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/12 22:33:36 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log(t_philo *ph, char *msg)
{
	pthread_mutex_lock(ph->mutx_table);
	ph->ms_now = ms_get_epoch();
	printf("%-8ld %-3d %s\n", ph->ms_now - *ph->ms_begin, ph->id, msg);
	pthread_mutex_unlock(ph->mutx_table);
}

int	philo_error(t_table *table, char *msg)
{
	printf("Error: %s\n", msg);
	free_all(table);
	return (1);
}
