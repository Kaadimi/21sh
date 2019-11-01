/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_copy_past_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:16:33 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:16:34 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	q_reverse_position(int len, t_counters *t)
{
	int i;
	int k;
	int virgin;

	virgin = 0;
	i = len - t->index;
	k = len + t->diff_index;
	while (i-- >= 0)
	{
		if (t->str[len--] == '\n')
		{
			up_to_edge(t);
			virgin = 1;
		}
		else
		{
			tputs(tgetstr("bw", NULL), 0, ft_outc);
			tputs(tgetstr("le", NULL), 0, ft_outc);
		}
		if (virgin == 0)
			t->inline_index++;
		else
			t->inline_index--;
	}
	t->inline_index++;
}

char	*mini_remove_strinstr(char *str, int size, int start)
{
	int		i;
	char	*new;

	i = 0;
	new = my_malloc(ft_intlen(str) - size + 1);
	while (i < start)
	{
		new[i] = str[i];
		i++;
	}
	while (str[start + size])
		new[i++] = str[start + size++];
	new[i] = '\0';
	free(str);
	return (new);
}

void	q_home_clear(t_counters t)
{
	int i;

	i = line_nb_in_quote(t.str, t.index, t.diff_index);
	while (i-- > 0)
		tputs(tgetstr("up", NULL), 0, ft_outc);
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	i = 0;
	while (i++ < t.diff_index)
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
}

void	q_ctl_past(t_counters *t)
{
	if (t->index < ft_intlen(t->str))
	{
		q_home_clear(*t);
		t->str = add_str_in_str(t);
		ft_putstr(t->str);
	}
	else
	{
		ft_putstr(t->copy_str);
		t->str = ft_freejoin(t->str, t->copy_str);
	}
	t->index += ft_intlen(t->copy_str);
	q_reverse_position(ft_intlen(t->str), t);
}

void	q_selection_remover(t_counters *t, int *direction, int *start)
{
	*direction = 0;
	*start = -1;
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	q_home_clear(*t);
	ft_putstr(t->str);
	tputs(tgetstr("rc", NULL), 0, ft_outc);
}
