/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:09:27 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/15 19:42:56 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	q_outside_copy(t_counters *t, char *buf)
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

void	delete_and_left(t_counters *t, char *buf)
{
	if (LEFT && t->index > 0)
	{
		if (!EDGE)
			tputs(tgetstr("le", NULL), 0, ft_outc);
		t->index--;
	}
	else if (DEL && t->index > 0)
	{
		if (EDGE)
			up_to_right();
		else
			tputs(tgetstr("le", NULL), 0, ft_outc);
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		ft_putstr(t->str + t->index);
		tputs(tgetstr("rc", NULL), 0, ft_outc);
		t->index--;
		t->str = index_remover(t->str, t->index);
	}
}

void	insert_and_right(t_counters *t, char *buf)
{
	if (RIGHT)
	{
		if (t->index < ft_intlen(t->str))
		{
			tputs(tgetstr("nd", NULL), 0, ft_outc);
			t->index++;
		}
		else
			t->bakara = 1;
	}
	else if (INSERT)
	{
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		write(1, &buf[0], 1);
		t->str = insert_char(t->str, buf[0], t->index);
		t->index++;
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		ft_putstr(t->str + t->index);
		tputs(tgetstr("rc", NULL), 0, ft_outc);
	}
}

void	up_key(t_history **head, t_counters *t, char *buf, int nb_nodes)
{
	if ((ft_strstr(t->str, "\n") && t->index == line_lenght(t->str)) ||
		(t->index == ft_intlen(t->str) && !ft_strstr(t->str, "\n")))
		if (UP && head && t->node_counter <= nb_nodes)
		{
			t->node_counter++;
			clear_all(line_lenght(t->str), t->diff_index);
			if (t->node_counter == 2)
				term_putstr((*head)->command, t->index + t->diff_index);
			else
			{
				if ((*head)->next != NULL)
					*head = (*head)->next;
				t->index = 0;
				term_putstr((*head)->command, t->index + t->diff_index);
			}
			ft_strdel(&t->str);
			t->str = ft_strdup((*head)->command);
			t->index = ft_intlen(t->str);
			if (ft_strstr(t->str, "\n"))
				start_position_quote(t);
		}
}

void	down_key(t_history **head, t_counters *t, char *buf)
{
	if ((ft_strstr(t->str, "\n") && t->index == line_lenght(t->str)) ||
			(t->index == ft_intlen(t->str) && !ft_strstr(t->str, "\n")))
		if (DOWN && *head && t->node_counter > 1)
		{
			t->node_counter--;
			clear_all(line_lenght(t->str), t->diff_index);
			if (t->node_counter > 1)
			{
				if ((*head)->prev != NULL)
					*head = (*head)->prev;
				t->index = 0;
				term_putstr((*head)->command, t->index + t->diff_index);
				ft_strdel(&t->str);
				t->str = ft_strdup((*head)->command);
				t->index = ft_intlen(t->str);
			}
			if (t->node_counter == 1)
			{
				free(t->str);
				t->str = ft_strdup("");
				t->index = 0;
			}
			if (ft_strstr(t->str, "\n"))
				start_position_quote(t);
		}
}
