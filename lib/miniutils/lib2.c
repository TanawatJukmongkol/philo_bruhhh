/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:48:29 by tjukmong          #+#    #+#             */
/*   Updated: 2023/05/14 01:57:51 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniutils.h"

static int	my_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static long	my_atol(const char *nptr)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\a' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
			nbr = (nbr * 10) + (*nptr - '0');
		else
			break ;
		nptr++;
	}
	return (sign * nbr);
}

int	*aaput_ai(int *i, int *res, char **argv)
{
	long	tmp;
	int		j;

	while (argv[*i])
	{
		j = 0;
		tmp = my_atol(argv[*i]);
		while (argv[*i][j])
		{
			if (j == 0 && argv[*i][j] == '+')
				j++;
			if (!my_isdigit(argv[*i][j]) || argv[*i][j] == '\0'
				|| tmp < INT_MIN || tmp > INT_MAX)
			{
				while (argv[*i])
					free(argv[(*i)++]);
				free(res);
				return (NULL);
			}
			j++;
		}
		res[*i] = tmp;
		free(argv[(*i)++]);
	}
	return (res);
}

int	*argv_aatoai(int *argc, char **argv)
{
	int	i;
	int	ac;
	int	*res;

	i = 0;
	ac = 0;
	while (argv[ac])
		ac++;
	*argc = ac;
	res = malloc(ac * sizeof(int));
	if (!res)
		return (NULL);
	i = 0;
	return (aaput_ai(&i, res, argv));
}
