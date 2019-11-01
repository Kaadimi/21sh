/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_home_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:04:41 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 16:04:42 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	q_home_button(int index, int diff_index)
{
	int i;

	i = 0;
	while (i < ((index + diff_index) / tgetnum("co")))
	{
		tputs(tgetstr("up", NULL), 0, ft_outc);
		i++;
	}
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	i = 0;
	while (i++ < diff_index)
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

void	q_end_button(int index)
{
	int i;

	i = 0;
	while (i < (index / tgetnum("co")))
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		i++;
	}
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	i = 0;
	while (i++ < (index % tgetnum("co")))
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

void	go_home(t_counters *t)
{
	if (t->inline_index == 0)
	{
		tputs(tgetstr("up", NULL), 0, ft_outc);
		t->index--;
		t->inline_index = index_finder(t->str + t->index,
		t->str, t->diff_index);
	}
	if ((t->index + t->diff_index) == t->inline_index)
	{
		q_home_button(t->inline_index, t->diff_index);
		t->index = 0;
		t->inline_index = t->diff_index;
	}
	else if (t->inline_index > 0)
	{
		q_home_button(t->inline_index, 0);
		t->index -= t->inline_index;
		t->inline_index = 0;
	}
}

void	go_end(t_counters *t)
{
	if (t->inline_index == index_finder(t->str + t->index,
	t->str, t->diff_index))
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("cr", NULL), 0, ft_outc);
		t->inline_index = 0;
		t->index++;
	}
	if (t->inline_index > 0)
		go_home(t);
	if (t->index == 0)
		q_end_button(line_lenght(t->str + t->index) + t->diff_index);
	else
		q_end_button(line_lenght(t->str + t->index));
	t->inline_index = index_finder(t->str + t->index, t->str, t->diff_index);
	if (t->index == 0)
		t->index += (t->inline_index - t->diff_index);
	else
		t->index += t->inline_index;
}

void	q_home_and_print(t_counters *t, char *buf)
{
	if (HOME)
		while (t->index > 0)
			q_backword_march(t);
	else if (END && t->index < ft_intlen(t->str))
		while (t->index < ft_intlen(t->str))
			q_forword_march(t);
	else if (!DEL && OUTPUT)
	{
		t->str = ft_freejoin(t->str, buf);
		ft_outc(buf[0]);
		t->index++;
	}
	else
		q_outside_copy(t, buf);
}
