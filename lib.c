/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:38:51 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/14 00:29:45 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*my_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destptr;
	unsigned char	*ptr;

	if (!dest && !src)
		return (NULL);
	destptr = dest;
	ptr = (unsigned char *)src;
	while (n-- > 0)
		*destptr++ = *ptr++;
	return (dest);
}

static int	my_splitlen(char const *s, char c)
{
	char	*str;
	int		len;
	int		flag;

	str = (char *)s;
	len = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && !flag)
		{
			len++;
			flag = 1;
		}
		else if (*str == c && flag)
			flag = 0;
		str++;
	}
	return (len);
}

static char	**my_free_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**my_put_table(char **res, char *str, char c, int len)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (a < len)
	{
		if (*str && *str != c)
			b++;
		else if (b != 0)
		{
			res[a] = malloc((b + 1) * sizeof(char));
			if (!res[a])
				return (my_free_arr(res));
			my_memcpy(res[a], str - b, b);
			res[a][b] = '\0';
			a++;
			b = 0;
		}
		str++;
	}
	return (res);
}

char	**argv_splitstr(char const *s, char c)
{
	char	**res;
	char	*str;
	int		len;

	if (!s)
		return (NULL);
	str = (char *)s;
	len = my_splitlen(s, c);
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[len] = NULL;
	return (my_put_table(res, str, c, len));
}
