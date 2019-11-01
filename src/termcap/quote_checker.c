/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:44:21 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:44:23 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_quote(t_counters t)
{
	int		line;
	int		index_line;

	line = line_nb_in_quote(t.str, -1, t.diff_index);
	index_line = line_nb_in_quote(t.str, t.index, t.diff_index);
	while (index_line <= line)
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		index_line++;
	}
}

int		parse_error(char *str, int index)
{
	int	len;

	len = 0;
	while (str[index] != '\0' && str[index] != '\n')
	{
		if (len > 0 && (str[index] == ' ' || str[index] == '\t'))
			break ;
		else if (str[index] != ' ' && str[index] != '\t')
			len++;
		index++;
	}
	if (len == 0)
		return (0);
	return (1);
}

int		ignore_quote(t_counters *t, int *i)
{
	if (t->tmp[*i] == '\'')
	{
		*i += 1;
		while (t->tmp[*i] != '\'' && t->tmp[*i] != '\0')
			*i += 1;
		if (t->tmp[*i] == '\0')
		{
			t->status = 1;
			return (0);
		}
	}
	if (t->tmp[*i] == '\"')
	{
		*i += 1;
		while (t->tmp[*i] != '\"' && t->tmp[*i] != '\0')
			*i += 1;
		if (t->tmp[*i] == '\0')
		{
			t->status = 2;
			return (0);
		}
	}
	return (1);
}

int		quote_checker_2(t_counters *t, int *j)
{
	int i;

	i = 0;
	while (t->tmp[i])
	{
		if (!ignore_quote(t, &i))
			return (0);
		if (t->tmp[i] == '<' && t->tmp[i + 1] == '<')
		{
			if (!parse_error(t->tmp, i + 2))
				return (1);
			t->herdoc++;
		}
		*j += 1;
		i++;
	}
	return (2);
}

int		quote_checker(t_counters *t)
{
	int		i;
	int		j;
	char	*usless;

	i = 0;
	j = 0;
	if (t->quote == 0)
		t->tmp = my_strdup(t->str);
	else if (t->quote > 0)
	{
		usless = ft_strjoin("\n", t->str);
		t->tmp = ft_freejoin(t->tmp, usless);
		ft_strdel(&usless);
	}
	i = quote_checker_2(t, &j);
	if (i == 0)
		return (0);
	else if (i == 1)
		return (1);
	if (t->status == 0 && t->herdoc > 0 && ft_strstr(t->tmp, "\n"))
		return (herdoc_checker(t, j));
	else if (t->status == 0 && t->herdoc > 0)
		return (0);
	return (1);
}
