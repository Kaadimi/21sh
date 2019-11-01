/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_past.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 13:40:04 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/15 19:32:42 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	new_right_selection(t_counters *t, int *direction, int *start)
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
	if (((t->index + t->diff_index) % tgetnum("co")) == 0)
		tputs(tgetstr("do", NULL), 0, ft_outc);
}

void	old_right_s(t_counters *t, int *direction, int *start, int *zero)
{
	if (*zero == 0)
	{
		*direction += 1;
		t->index++;
		t->save = t->index;
		if (((t->index + t->diff_index) % tgetnum("co")) == 0)
			tputs(tgetstr("do", NULL), 0, ft_outc);
		else
			tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	else
		*zero = 0;
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

void	copy_cut_past(t_counters *t, int *direction, int *start, int *zero)
{
	if (t->actions == 3 && (*direction != 0 || *zero == -1))
	{
		ctl_copy(t, *start, *direction, *zero);
		selection_remover(t, direction, start);
	}
	else if (t->actions == 4 && t->copy_str)
		ctl_past(t);
	else if (t->actions == 5 && (*direction != 0 || *zero == -1))
	{
		ctl_copy(t, *start, *direction, *zero);
		ctl_cut(t, *direction, *start, *zero);
		direction = 0;
		*start = -1;
	}
}

void	copy_actions(t_counters *t, char *buf)
{
	if (!ft_strcmp(buf, "≥"))
		t->actions = 1;
	else if (!ft_strcmp(buf, "≤"))
		t->actions = 2;
	else if (!ft_strcmp(buf, "ç"))
		t->actions = 3;
	else if (!ft_strcmp(buf, "√"))
		t->actions = 4;
	else if (!ft_strcmp(buf, "≈"))
		t->actions = 5;
	else
		t->actions = 0;
}

void	copy_past(t_counters *t, char *buf)
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
		new_right_selection(t, &direction, &start);
	else if (t->actions == 2 && t->index >= 0 &&
			direction <= 0 && zero == 0 && ft_intlen(t->str) >= 1)
		new_left_selection(t, &direction, &start, &zero);
	else if (t->actions == 2 && t->index >= 0 && direction > 0)
		old_left_selection(t, &direction);
	else if (t->actions == 1 && t->index >= 0 && direction < 0)
		old_right_s(t, &direction, &start, &zero);
	else if (t->actions == 3 || t->actions == 4 || t->actions == 5)
		copy_cut_past(t, &direction, &start, &zero);
	else if ((direction != 0 || zero == -1) && t->actions == 0)
		selection_remover(t, &direction, &start);
}
