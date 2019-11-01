/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_past_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:06:06 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:06:08 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*add_str_in_str(t_counters *t)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = ft_intlen(t->str) + ft_intlen(t->copy_str);
	new = my_malloc(i + 1);
	i = 0;
	while (i < t->index)
	{
		new[i] = t->str[i];
		i++;
	}
	while (t->copy_str[j])
		new[i++] = t->copy_str[j++];
	j = t->index;
	while (t->str[j])
		new[i++] = t->str[j++];
	new[i] = '\0';
	ft_strdel(&t->str);
	return (new);
}

char	*remove_str_2(t_counters *t, int direction, int start, int i)
{
	char *new;

	new = NULL;
	if (direction < 0)
	{
		start++;
		new = my_malloc(ft_intlen(t->str) + direction + 1);
		while (i <= t->index)
		{
			new[i] = t->str[i];
			i++;
		}
		while (t->str[start])
			new[i++] = t->str[start++];
	}
	new[i] = '\0';
	return (new);
}

char	*remove_str_in_str(t_counters *t, int direction, int start, int zero)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	if (zero == -1 && t->index == 0)
		t->index--;
	if (direction < 0)
		new = remove_str_2(t, direction, start, i);
	else
	{
		new = my_malloc(ft_intlen(t->str) - direction + 1);
		while (i < start)
		{
			new[i] = t->str[i];
			i++;
		}
		while (t->str[start + direction])
			new[i++] = t->str[start + direction++];
		new[i] = '\0';
	}
	if (zero == -1 && t->index == -1)
		t->index++;
	ft_strdel(&t->str);
	return (new);
}

void	reverse_position(int index, int diff_index, int len)
{
	int	i;
	int	k;

	i = len - index;
	k = len + diff_index;
	ft_itoa(k);
	while (i-- > 0)
	{
		tputs(tgetstr("bw", NULL), 0, ft_outc);
		tputs(tgetstr("le", NULL), 0, ft_outc);
	}
}

void	selection_remover(t_counters *t, int *direction, int *start)
{
	*direction = 0;
	*start = -1;
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	home_button(t->index, t->diff_index);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	ft_putstr(t->str);
	tputs(tgetstr("rc", NULL), 0, ft_outc);
}
