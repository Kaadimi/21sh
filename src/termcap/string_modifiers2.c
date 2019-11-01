/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_modifiers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 20:52:04 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/05 22:12:27 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char		*fr;

	if (s1 && s2)
	{
		if (!(fr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		ft_strcat(ft_strcpy(fr, s1), s2);
		free((char *)s1);
		s1 = NULL;
		return (fr);
	}
	return (0);
}

int		search_in_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_isnum(char *vl)
{
	int		i;

	i = 0;
	while (vl[i])
	{
		if (vl[i] < '0' || vl[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

char	**ft_split(char *res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		if (res[i] == ' ' || res[i] == '\t')
			res[i] = -1;
		i++;
	}
	return (ft_strsplit(res, -1));
}

char	*ft_prepare(char *av)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup(av);
	while (res[i])
	{
		i = ignore_quot(res, i);
		if (res[i] == '>' || res[i] == '<' || res[i] == '&')
		{
			if ((res[i] == '&' && (res[i + 1] == '>' || res[i + 1] == '<'
			|| res[i - 1] == '<' || res[i - 1] == '>')) || res[i] == '>'
					|| res[i] == '<')
			{
				i = find_index_to_insert_sp(&res, i);
				res = insert_char(res, ' ', i);
			}
		}
		if (!res[i])
			break ;
		i++;
	}
	return (res);
}
