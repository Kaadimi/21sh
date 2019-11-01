/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:47:03 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:47:04 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_intlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ctrl_d_2(t_counters *t)
{
	int		i;
	char	*search;

	i = 0;
	while (t->tmp[i])
	{
		ignore_quote(t, &i);
		if (t->tmp[i] == '<' && t->tmp[i + 1] == '<')
		{
			search = end_of_doc(i + 2, t->tmp);
			if (search != NULL)
			{
				t->tmp = ft_freejoin(t->tmp, ft_strjoin("\n", search));
				free(search);
			}
		}
		i++;
	}
	write(1, "\n", 1);
}

int		ctrl_d_checker(t_counters *t)
{
	int i;

	i = 0;
	if (t->quote > 0)
	{
		while (t->tmp[i])
		{
			if (!ignore_quote(t, &i))
				return (0);
			if (t->tmp[i] == '<' && t->tmp[i + 1] == '<')
				t->herdoc++;
			i++;
		}
		if (t->herdoc > 0)
			return (0);
	}
	return (1);
}

int		ft_ctrl_2d(t_counters *t, int *nb_nodes, t_history **head)
{
	if (t->status == 2)
	{
		ft_putstr("\nunexpected EOF while looking for matching '\"'\n");
		t->tmp = ft_freejoin(t->tmp, "\"");
		t->error = 1;
	}
	else if (t->status == 1)
	{
		ft_putstr("\nunexpected EOF while looking for matching '\''\n");
		t->tmp = ft_freejoin(t->tmp, "\'");
		t->error = 1;
	}
	else
		ctrl_d_2(t);
	*nb_nodes += 1;
	*head = t->start;
	free(t->str);
	return (1);
}

int		ft_ctrl_d(t_counters *t, int *nb_nodes, t_history **head)
{
	if (ft_intlen(t->str) > 0)
		return (0);
	else if (ft_intlen(t->str) == 0 && ctrl_d_checker(t))
	{
		ft_strdel(&t->str);
		ft_strdel(&t->tmp);
		ft_strdel(&t->copy_str);
		exit(0);
	}
	else if (ft_intlen(t->str) == 0)
		return (ft_ctrl_2d(t, nb_nodes, head));
	return (0);
}
