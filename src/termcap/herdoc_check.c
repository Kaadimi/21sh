/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:41:43 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/06 14:38:44 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	avoid_quote(char *str, int *i)
{
	if (str[*i - 1] == '\'')
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i += 1;
		*i += 1;
	}
	if (str[*i - 1] == '\"')
	{
		while (str[*i] != '\"' && str[*i] != '\0')
			*i += 1;
		*i += 1;
	}
}

char	*n9i_el_garga3(char *str, int j)
{
	char	*clean;
	int		i;
	int		k;

	i = 0;
	k = 0;
	clean = my_malloc(j + 1);
	while (str[i])
	{
		avoid_quote(str, &i);
		if (i >= ft_intlen(str))
			break ;
		clean[k++] = str[i++];
	}
	clean[k] = '\0';
	return (clean);
}

int		herdoc_checker_3(t_counters *t, int *k, char **split, char *search)
{
	if (*k == 0)
	{
		ft_strdel(&search);
		tab_free(split);
		return (0);
	}
	if (!ft_strcmp(split[*k], search))
	{
		t->herdoc--;
		*k -= 1;
	}
	if (t->herdoc == 0)
	{
		ft_strdel(&search);
		tab_free(split);
		return (1);
	}
	return (2);
}

int		herdoc_checker_2(t_counters *t, int k, char **split, int i)
{
	char	*search;
	int		j;

	j = 0;
	while (i >= 0)
	{
		if (t->tmp[i] == '<' && t->tmp[i + 1] == '<')
		{
			search = end_of_doc(i + 2, t->tmp);
			while (ft_strcmp(split[k], search) && k > 0)
				k--;
			j = herdoc_checker_3(t, &k, split, search);
			if (j == 1)
				return (1);
			else if (j == 0)
				return (0);
			ft_strdel(&search);
		}
		i--;
	}
	return (0);
}

int		herdoc_checker(t_counters *t, int j)
{
	int		i;
	int		k;
	char	**split;
	char	*hchuma;

	i = ft_intlen(t->tmp);
	k = 0;
	hchuma = n9i_el_garga3(t->tmp, j);
	split = ft_strsplit(hchuma, '\n');
	ft_strdel(&hchuma);
	while (split[k])
		k++;
	k--;
	return (herdoc_checker_2(t, k, split, i));
}
