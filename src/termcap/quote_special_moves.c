/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_special_moves.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:10:18 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/04 21:10:19 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	q_backword_march(t_counters *t)
{
	t->index--;
	t->inline_index--;
	if (t->str[t->index] == '\n')
		up_to_edge(t);
	else if (((t->inline_index + 1) % tgetnum("co")) == 0)
		up_to_right();
	else
		tputs(tgetstr("le", NULL), 0, ft_outc);
}

void	q_forword_march(t_counters *t)
{
	t->index++;
	t->inline_index++;
	if (((t->inline_index) % tgetnum("co")) == 0)
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("cr", NULL), 0, ft_outc);
	}
	else if (t->str[t->index - 1] == '\n')
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("cr", NULL), 0, ft_outc);
		t->inline_index = 0;
	}
	else
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

bool	q_space_before(t_counters t)
{
	int i;

	i = 0;
	while (i < t.index)
		if (t.str[i++] == ' ')
			return (true);
	return (false);
}

void	q_prev_next_word(t_counters *t, char *buf)
{
	if (PREV_WORD && space_before(*t))
	{
		if (t->str[t->index] == ' ' || t->str[t->index] == '\n')
			q_backword_march(t);
		while (t->str[t->index] != ' ' && t->str[t->index] != '\n')
			q_backword_march(t);
		while (t->str[t->index - 1] == ' ' || t->str[t->index - 1] == '\n')
			q_backword_march(t);
	}
	else if (NEXT_WORD)
	{
		while ((t->str[t->index] == ' ' || t->str[t->index] == '\n')
				&& t->str[t->index])
			q_forword_march(t);
		while (t->str[t->index] != ' ' && t->str[t->index] != '\n'
				&& t->str[t->index])
			q_forword_march(t);
	}
}

void	q_prev_next_line(t_counters *t, char *buf)
{
	if (PREV_LINE && q_line_before(*t))
	{
		if (t->str[t->index] == '\n')
			q_backword_march(t);
		while (t->str[t->index] != '\n')
			q_backword_march(t);
	}
	else if (NEXT_LINE)
	{
		if (t->str[t->index] == '\n' && t->str[t->index])
			q_forword_march(t);
		while (t->str[t->index] != '\n' && t->str[t->index])
			q_forword_march(t);
	}
}
