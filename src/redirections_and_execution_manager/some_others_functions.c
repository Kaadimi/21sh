/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_others_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:10:53 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 17:48:45 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			repare_env_c(char **env_c)
{
	int		i;
	int		j;

	i = 0;
	while (env_c[i])
	{
		j = 0;
		while (env_c[i][j])
			j++;
		env_c[i][j] = '=';
		i++;
	}
}

static char		*delete_qout_assist(char *vl, int *i, int mode)
{
	if (mode == 1)
	{
		vl = index_remover(vl, *i);
		if (*i > 0)
			*i -= 1;
		*i = delete_qout_agent(vl, *i, '"');
		vl = index_remover(vl, *i);
		if (vl[*i] == '"')
			vl = delete_qout_assist(vl, i, 1);
		return (vl);
	}
	vl = index_remover(vl, *i);
	if (*i > 0)
		*i -= 1;
	*i = delete_qout_agent(vl, *i, 39);
	vl = index_remover(vl, *i);
	if (vl[*i] == 39)
		vl = delete_qout_assist(vl, i, 2);
	return (vl);
}

char			*delete_qout(char *vl)
{
	int		i;

	i = 0;
	while (vl[i])
	{
		if (vl[i] == '"')
			vl = delete_qout_assist(vl, &i, 1);
		if (vl[i] == 39)
			vl = delete_qout_assist(vl, &i, 2);
		if (!vl[i])
			break ;
		i++;
	}
	return (vl);
}

char			*find_replace(char *haystack, char *find, char *replace)
{
	size_t		i;
	size_t		j;
	char		*p;
	size_t		h;

	i = 0;
	j = 0;
	h = ft_strlen(find);
	while (haystack[i])
	{
		i = ignore_quot(haystack, i);
		j = 0;
		while (haystack[i + j] == find[j])
		{
			if (find[j + 1] == '\0')
			{
				p = ft_new_stack(haystack, replace, i, h);
				free(haystack);
				return (p);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char			*ft_new_stack(char *haystack, char *replace, size_t a, size_t j)
{
	size_t		i;
	size_t		k;
	size_t		o;
	char		*newstack;

	i = ft_strlen(replace) + ft_strlen(haystack) - j + 1;
	newstack = (char *)malloc(sizeof(char) * i);
	ft_memset(newstack, '0', i);
	o = a;
	k = 0;
	ft_strncpy(newstack, haystack, a);
	while (replace[k])
		newstack[a++] = replace[k++];
	while (a < i)
		newstack[a++] = haystack[o + j++];
	newstack[a] = '\0';
	return (newstack);
}
