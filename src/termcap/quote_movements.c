/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:56:48 by ikadimi           #+#    #+#             */
/*   Updated: 2019/04/29 12:56:50 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	q_line_before(t_counters t)
{
	int i;

	i = 0;
	while (i < t.index)
		if (t.str[i++] == '\n')
			return (true);
	return (false);
}

int		line_lenght(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

int		line_nb_in_quote(char *str, int index, int diff)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = diff;
	while (str[i])
	{
		if (i == index)
			break ;
		if (str[i] == '\n')
		{
			j += (k / tgetnum("co"));
			k = -2;
			j++;
		}
		k++;
		i++;
	}
	j += (k / tgetnum("co"));
	return (j);
}

void	q_delete_and_left(t_counters *t, char *buf)
{
	if (LEFT && t->index > 0)
	{
		if (t->str[t->index - 1] != '\n'
		&& (t->inline_index % tgetnum("co")) != 0)
			tputs(tgetstr("le", NULL), 1, ft_outc);
		t->index--;
		t->inline_index--;
	}
	else if (DEL && t->index > 0)
	{
		t->index--;
		t->inline_index--;
		if (t->str[t->index] == '\n')
			up_to_edge(t);
		else if (((t->inline_index + 1) % tgetnum("co")) == 0 &&
		t->inline_index > 1)
			up_to_right();
		else
			tputs(tgetstr("le", NULL), 0, ft_outc);
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		q_term_putstr(t->str + t->index + 1, t->index + t->diff_index);
		tputs(tgetstr("rc", NULL), 0, ft_outc);
		t->str = index_remover(t->str, t->index);
	}
}

void	q_insert_and_right(t_counters *t, char *buf)
{
	if (RIGHT)
	{
		if (t->index < ft_intlen(t->str))
		{
			tputs(tgetstr("nd", NULL), 0, ft_outc);
			t->index++;
			t->inline_index++;
		}
		else
			t->bakara = 1;
	}
	else if (INSERT)
	{
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		write(1, &buf[0], 1);
		t->str = insert_char(t->str, buf[0], t->index);
		t->index++;
		t->inline_index++;
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		q_term_putstr(t->str + t->index, t->index + t->diff_index);
		tputs(tgetstr("rc", NULL), 0, ft_outc);
	}
}
