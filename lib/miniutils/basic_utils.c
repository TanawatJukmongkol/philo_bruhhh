/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:04:59 by tjukmong          #+#    #+#             */
/*   Updated: 2023/05/14 02:12:01 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniutils.h"

size_t	argv_joinstrlen(char **argv)
{
	size_t	final_len;
	int		i;
	int		j;

	final_len = 0;
	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			j++;
		final_len += (j + 1);
		i++;
	}
	return (final_len);
}

char	*argv_joinstr(char **argv)
{
	size_t	final_len;
	char	*res;
	int		i;
	int		j;
	int		k;

	final_len = argv_joinstrlen(argv);
	if (final_len == 0)
		return (NULL);
	res = malloc(final_len + 1);
	if (!res)
		return (NULL);
	i = 1;
	k = 0;
	while (argv[i])
	{
		j = 0;
		res[k++] = ' ';
		while (argv[i][j])
			res[k++] = argv[i][j++];
		i++;
	}
	res[final_len] = '\0';
	return (res);
}

int	*argv_getint(int *argc, char **argv)
{
	char	*str;
	char	**split;
	int		*res;
	int		i;

	i = 0;
	*argc = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			return (NULL);
		i++;
	}
	str = argv_joinstr(argv);
	if (!str)
		return (NULL);
	split = argv_splitstr(str, ' ');
	free(str);
	if (!split)
		return (NULL);
	res = argv_aatoai(argc, split);
	free(split);
	return (res);
}
