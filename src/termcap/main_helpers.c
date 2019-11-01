/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:50:17 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/05 15:50:18 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	doc_quote_printers(t_counters *t)
{
	if (t->status == 1)
	{
		t->diff_index = 7;
		ft_putstr("\e[31mquote>\e[0m ");
	}
	else if (t->status == 2)
	{
		t->diff_index = 8;
		ft_putstr("\e[31mdquote>\e[0m ");
	}
	else if (t->herdoc > 0)
	{
		t->diff_index = 9;
		ft_putstr("\e[31mheredoc>\e[0m ");
	}
}

void	calling_center(t_counters *t, char *buf)
{
	if (!ft_strstr(t->str, "\n"))
	{
		copy_past(t, buf);
		prev_next_line(t, buf);
		prev_next_word(t, buf);
		home_and_print(t, buf);
		delete_and_left(t, buf);
		insert_and_right(t, buf);
		edge_warden(t, buf);
	}
	else if (ft_strstr(t->str, "\n"))
	{
		q_prev_next_line(t, buf);
		q_copy_past(t, buf);
		q_prev_next_word(t, buf);
		q_home_and_print(t, buf);
		q_delete_and_left(t, buf);
		q_insert_and_right(t, buf);
		quote_edge(t, buf);
	}
}

void	remove_info(t_counters *t)
{
	home_button(t->index, t->diff_index);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	ft_putstr(t->str);
	t->autoc = 0;
}

int		escape_or_not(t_counters *t, char *buf, int *nb_nodes, t_history **head)
{
	if (t->autoc == 1)
		remove_info(t);
	if (buf[0] == '\n' && t->ret == 1 && quote_checker(t))
	{
		if (ft_intlen(t->str) == 0)
			prompt_printer(t, 1);
		else
		{
			*nb_nodes += 1;
			*head = t->start;
			clear_quote(*t);
			ft_strdel(&t->str);
			return (1);
		}
	}
	else if (buf[0] == '\n' && ft_intlen(t->str) > 0 && t->ret == 1)
	{
		clear_quote(*t);
		ft_strdel(&t->str);
		t->str = my_strdup("");
		doc_quote_printers(t);
		t->index = 0;
		t->quote++;
	}
	return (0);
}

void	prompt_printer(t_counters *t, int k)
{
	char	cwd[255];
	char	**cmd;
	int		i;

	i = 0;
	if (k == 1)
		ft_putstr("\n");
	getcwd(cwd, 255);
	if (!ft_strcmp(cwd, "/"))
	{
		ft_putstr("\e[1;96m/ ⇢ \e[0m");
		t->diff_index = 4;
		return ;
	}
	cmd = ft_strsplit(cwd, '/');
	while (cmd[i])
		i++;
	ft_putstr("\e[1;96m");
	ft_putstr(cmd[i - 1]);
	ft_putstr(" ⇢ \e[0m");
	t->diff_index = ft_intlen(cmd[i - 1]) + 3;
	tab_free(cmd);
}
