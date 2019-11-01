/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_past_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:08:46 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:08:47 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ctl_copy(t_counters *t, int start, int direction, int zero)
{
	int	i;

	i = 0;
	if (zero == -1)
		direction--;
	if (direction < 0)
	{
		if (t->copy_str != NULL)
			ft_strdel(&t->copy_str);
		t->copy_str = my_malloc((direction * -1) + 1);
		while (++direction <= 0)
			t->copy_str[i++] = t->str[start + direction];
	}
	else if (direction > 0)
	{
		if (t->copy_str != NULL)
			ft_strdel(&t->copy_str);
		t->copy_str = my_malloc(direction + 1);
		while (--direction >= 0)
			t->copy_str[i++] = t->str[start++];
	}
	t->copy_str[i] = '\0';
}

void	ctl_past(t_counters *t)
{
	if (t->index < ft_intlen(t->str))
	{
		home_button(t->index, t->diff_index);
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		t->str = add_str_in_str(t);
		ft_putstr(t->str);
	}
	else
	{
		ft_putstr(t->copy_str);
		t->str = ft_freejoin(t->str, t->copy_str);
	}
	t->index += ft_intlen(t->copy_str);
	reverse_position(t->index, t->diff_index, ft_intlen(t->str));
}

void	clt_cut_2(t_counters *t)
{
	home_button(t->index, t->diff_index);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	t->copy_str = my_strdup(t->str);
	ft_strdel(&t->str);
	t->str = my_strdup("");
	t->index = 0;
}

void	ctl_cut(t_counters *t, int direction, int start, int zero)
{
	int i;

	if (zero == -1)
		direction--;
	if (ft_intlen(t->str) == direction ||
			(zero == -1 && ft_intlen(t->str) == -direction))
		clt_cut_2(t);
	else
	{
		i = ft_intlen(t->str);
		home_button(t->index, t->diff_index);
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		t->str = remove_str_in_str(t, direction, start, zero);
		ft_putstr(t->str);
		if (direction < 0)
			reverse_position(t->index, t->diff_index, ft_intlen(t->str));
		else
		{
			reverse_position(t->index, t->diff_index, i);
			t->index -= ft_intlen(t->copy_str);
		}
	}
}
