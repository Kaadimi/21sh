/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_copy_past_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:19:07 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:19:08 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	q_ctl_cut(t_counters *t, int direction, int start, int zero)
{
	if (zero == -1)
		direction--;
	if (ft_intlen(t->str) == direction ||
			(zero == -1 && ft_intlen(t->str) == -direction))
	{
		q_home_clear(*t);
		t->copy_str = my_strdup(t->str);
		free(t->str);
		t->str = my_strdup("");
		t->index = 0;
	}
	else
	{
		q_home_clear(*t);
		t->str = remove_str_in_str(t, direction, start, zero);
		ft_putstr(t->str);
		if (direction < 0)
			q_reverse_position(ft_intlen(t->str), t);
		else
		{
			t->index -= direction;
			q_reverse_position(ft_intlen(t->str), t);
		}
	}
}

void	q_new_right_s(t_counters *t, int *direction, int *start)
{
	if (*start == -1)
		*start = t->index;
	*direction += 1;
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("mr", NULL), 0, ft_outc);
	ft_putstr("\x1b[36m");
	write(1, &t->str[t->index], 1);
	tputs(tgetstr("me", NULL), 0, ft_outc);
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	ft_putstr(t->str + t->index + 1);
	tputs(tgetstr("rc", NULL), 0, ft_outc);
	t->index++;
	t->inline_index++;
	if (((t->inline_index % tgetnum("co")) == 0
				&& t->inline_index > 0))
		tputs(tgetstr("do", NULL), 0, ft_outc);
	else if (t->str[t->index - 1] == '\n')
		t->inline_index = 0;
}

void	q_new_left_2(t_counters *t, int *direction, int *zero)
{
	if (t->index > 0)
	{
		t->index--;
		t->inline_index--;
		*direction -= 1;
		if (t->str[t->index] == '\n')
			up_to_edge(t);
		else
			tputs(tgetstr("le", NULL), 0, ft_outc);
	}
	else
		*zero = -1;
}

void	q_new_left_s(t_counters *t, int *start, int *direction, int *zero)
{
	if (t->index == ft_intlen(t->str))
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		t->index--;
		t->inline_index--;
	}
	else
	{
		if (*start == -1)
			*start = t->index;
		t->save = t->index;
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		tputs(tgetstr("mr", NULL), 0, ft_outc);
		ft_putstr("\x1b[35m");
		while (t->save <= *start)
			write(1, &t->str[t->save++], 1);
		tputs(tgetstr("me", NULL), 0, ft_outc);
		ft_putstr(t->str + t->save);
		tputs(tgetstr("rc", NULL), 0, ft_outc);
		q_new_left_2(t, direction, zero);
	}
}
