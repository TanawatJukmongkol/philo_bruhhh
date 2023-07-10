/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniutils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:06:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/05/14 03:34:08 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIUTILS_H
# define MINIUTILS_H

# include <stdlib.h>
# include <limits.h>

int		*argv_getint(int *argc, char **argv);
char	**argv_splitstr(char const *s, char c);
int		*argv_aatoai(int *argc, char **argv);

#endif
