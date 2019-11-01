/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_copy_past.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:24:19 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/03 14:34:46 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	q_old_left_s(t_counters *t, int *direction)
{
	*direction -= 1;
	t->index--;
	t->inline_index--;
	if (t->str[t->index] == '\n')
		up_to_edge(t);
	else
		tputs(tgetstr("le", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	ft_putstr(t->str + t->index);
	tputs(tgetstr("rc", NULL), 0, ft_outc);
}

void	q_old_right_2(t_counters *t, int *start)
{
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	write(1, &t->str[t->save++], 1);
	tputs(tgetstr("mr", NULL), 0, ft_outc);
	ft_putstr("\x1b[35m");
	while (t->save <= *start)
		write(1, &t->str[t->save++], 1);
	tputs(tgetstr("me", NULL), 0, ft_outc);
	ft_putstr(t->str + t->save);
	tputs(tgetstr("rc", NULL), 0, ft_outc);
}

void	q_old_right_s(t_counters *t, int *direction, int *start, int *zero)
{
	if (*zero == 0)
	{
		*direction += 1;
		t->index++;
		t->inline_index++;
		t->save = t->index;
		if (((t->inline_index) % tgetnum("co")) == 0)
			tputs(tgetstr("do", NULL), 0, ft_outc);
		else if (t->str[t->index - 1] == '\n')
		{
			tputs(tgetstr("do", NULL), 0, ft_outc);
			t->inline_index = 0;
		}
		else
			tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	else
		*zero = 0;
	q_old_right_2(t, start);
}

void	q_copy_cut_past(t_counters *t, int *direction, int *start, int *zero)
{
	if (t->actions == 3 && (*direction != 0 || *zero == -1))
	{
		ctl_copy(t, *start, *direction, *zero);
		q_selection_remover(t, direction, start);
	}
	else if (t->actions == 4 && t->copy_str)
		q_ctl_past(t);
	else if (t->actions == 5 && (*direction != 0 || *zero == -1))
	{
		ctl_copy(t, *start, *direction, *zero);
		q_ctl_cut(t, *direction, *start, *zero);
		direction = 0;
		*start = -1;
	}
}

void	q_copy_past(t_counters *t, char *buf)
{
	static int start = -1;
	static int direction = 0;
	static int zero = 0;

	t->save = 0;
	copy_actions(t, buf);
	if (t->index > 0)
		zero = 0;
	if (t->actions == 1 && t->index < ft_intlen(t->str)
			&& direction >= 0 && ft_intlen(t->str) >= 1)
		q_new_right_s(t, &direction, &start);
	else if (t->actions == 2 && t->index >= 0 &&
			direction <= 0 && zero == 0 && ft_intlen(t->str) >= 1)
		q_new_left_s(t, &start, &direction, &zero);
	else if (t->actions == 2 && t->index >= 0 && direction > 0)
		q_old_left_s(t, &direction);
	else if (t->actions == 1 && t->index >= 0 && direction < 0)
		q_old_right_s(t, &direction, &start, &zero);
	else if (t->actions == 3 || t->actions == 4 || t->actions == 5)
		q_copy_cut_past(t, &direction, &start, &zero);
	else if ((direction != 0 || zero == -1) && t->actions == 0)
		q_selection_remover(t, &direction, &start);
}
