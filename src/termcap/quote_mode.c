/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:24:54 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/04 21:14:52 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		index_finder(char *find, char *str, int diff)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (str[0] == '\n' && find[0] == '\n')
		return (diff);
	while (find[i] != '\n' && find[i] != '\0')
		i++;
	i--;
	while (find[i] != '\n' && find + i != str)
	{
		i--;
		j++;
	}
	if (find + i == str)
		j += (diff + 1);
	return (j - 1);
}

void	start_position_quote(t_counters *t)
{
	int line;
	int chars;
	int i;

	line = line_nb_in_quote(t->str, -1, t->diff_index);
	chars = line_lenght(t->str) + t->diff_index;
	i = 0;
	while (i++ < line)
		tputs(tgetstr("up", NULL), 0, ft_outc);
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	i = 0;
	while (i++ < chars)
	{
		if ((i % tgetnum("co")) == 0 && i > 0)
			tputs(tgetstr("do", NULL), 0, ft_outc);
		else
			tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	t->index = line_lenght(t->str);
	t->inline_index = t->index + t->diff_index;
}

void	up_to_edge(t_counters *t)
{
	int i;

	i = 0;
	tputs(tgetstr("up", NULL), 0, ft_outc);
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	t->inline_index = index_finder(t->str + t->index, t->str, t->diff_index);
	while (++i <= (t->inline_index % tgetnum("co")))
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

void	khwi_tri9(t_counters *t)
{
	int line;
	int i;

	i = 0;
	line = line_nb_in_quote(t->str + t->index, -1, t->diff_index);
	while (i++ <= line)
		tputs(tgetstr("do", NULL), 0, ft_outc);
	while (i-- > 1)
		tputs(tgetstr("up", NULL), 0, ft_outc);
	i = 0;
	while (i++ < (t->inline_index % tgetnum("co")))
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

void	quote_edge(t_counters *t, char *buf)
{
	if (t->str[t->index - 1] == '\n' && (RIGHT || INSERT))
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("cr", NULL), 0, ft_outc);
		t->inline_index = 0;
	}
	if ((index_finder(t->str + t->index + 1, t->str, t->diff_index)
	% tgetnum("co")) == 0 && index_finder(t->str + t->index + 1,
	t->str, t->diff_index) > 0 && !DEL)
		khwi_tri9(t);
	else if (((t->inline_index % tgetnum("co")) == 0
				&& t->inline_index > 0) && (RIGHT || INSERT))
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("cr", NULL), 0, ft_outc);
	}
	if (t->str[t->index] == '\n' && LEFT)
		up_to_edge(t);
	else if ((t->inline_index + 1) % tgetnum("co") == 0 && LEFT
		&& t->inline_index > 0)
		up_to_right();
}
