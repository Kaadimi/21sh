/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:17:07 by ikadimi           #+#    #+#             */
/*   Updated: 2019/07/27 20:33:33 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tab_remover(t_counters *t, char *buf)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (buf[i])
	{
		if (buf[i] != '\t')
			k++;
		i++;
	}
	if (t->copy_str != NULL)
		free(t->copy_str);
	t->copy_str = my_malloc(k + 1);
	i = 0;
	k = 0;
	while (buf[i])
	{
		if (buf[i] != '\t')
			t->copy_str[k++] = buf[i];
		i++;
	}
	t->copy_str[k] = '\0';
}

void	home_button(int index, int diff_index)
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

void	end_button(int index)
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

void	outside_copy(t_counters *t, char *buf)
{
	if (!DEL && t->ret > 1 && str_is_print(buf))
	{
		tab_remover(t, buf);
		if (t->index == ft_intlen(t->str))
		{
			t->str = ft_freejoin(t->str, t->copy_str);
			ft_putstr(t->copy_str);
			t->index += ft_intlen(t->copy_str);
			t->inline_index = index_finder(t->str + t->index,
			t->str, t->diff_index);
		}
		else
		{
			tputs(tgetstr("cd", NULL), 0, ft_outc);
			ft_putstr(t->copy_str);
			t->str = add_str_in_str(t);
			t->index += ft_intlen(t->copy_str);
			ft_putstr(t->str + t->index);
			q_reverse_position(ft_intlen(t->str), t);
			tputs(tgetstr("nd", NULL), 0, ft_outc);
		}
	}
}

void	home_and_print(t_counters *t, char *buf)
{
	if (HOME && t->index > 0)
	{
		home_button(t->index, t->diff_index);
		t->index = 0;
	}
	else if (END && t->index < ft_intlen(t->str))
	{
		home_button(t->index, t->diff_index);
		end_button(ft_intlen(t->str) + t->diff_index);
		t->index = ft_intlen(t->str);
	}
	else if (!DEL && OUTPUT)
	{
		t->str = ft_freejoin(t->str, buf);
		ft_outc(buf[0]);
		t->index++;
	}
	else
		outside_copy(t, buf);
}
