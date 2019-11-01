/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_past_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:10:47 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:10:48 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		str_is_print(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if ((buf[i] < 32 || buf[i] > 126) && buf[i] != ' ' &&
		buf[i] != '\n' && buf[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	clear_all(int index, int diff_index)
{
	home_button(index, diff_index);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
}

void	new_left_selection_2(t_counters *t, int *direction, int *zero)
{
	if (t->index > 0)
	{
		if (((t->index + t->diff_index) % tgetnum("co")) == 0)
			up_to_right();
		else
			tputs(tgetstr("le", NULL), 0, ft_outc);
		t->index--;
		*direction -= 1;
	}
	else
		*zero = -1;
}

void	new_left_selection(t_counters *t, int *direction, int *start, int *zero)
{
	if (t->index == ft_intlen(t->str))
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		t->index--;
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
		new_left_selection_2(t, direction, zero);
	}
}

void	old_left_selection(t_counters *t, int *direction)
{
	*direction -= 1;
	t->index--;
	if (((t->index + 1 + t->diff_index) % tgetnum("co")) == 0)
		up_to_right();
	else
		tputs(tgetstr("le", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	ft_putstr(t->str + t->index);
	tputs(tgetstr("rc", NULL), 0, ft_outc);
}
