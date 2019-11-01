/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:41:03 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 20:11:43 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_for_eod(char *str, int index)
{
	int	len;

	len = 0;
	while (str[index] != '\0' && str[index] != '\n')
	{
		if (len > 0 && (str[index] == ' ' || str[index] == '\t' ||
		str[index] == '<' || str[index] == '>' || str[index] == ';'
		|| str[index] == '&'))
			break ;
		else if (str[index] != ' ' && str[index] != '\t' &&
		str[index] != '<' && str[index] != '>' && str[index] != ';'
		&& str[index] != '&')
			len++;
		index++;
	}
	return (len);
}

char	*end_of_doc(int index, char *str)
{
	int		len;
	char	*eof;

	len = 0;
	len = check_for_eod(str, index);
	if (len == 0)
		return (NULL);
	eof = my_malloc(len + 1);
	len = 0;
	while (str[index] != '\0' && str[index] != '\n')
	{
		if (len > 0 && (str[index] == ' ' || str[index] == '\t' ||
			str[index] == '<' || str[index] == '>' || str[index] == ';'
			|| str[index] == '&'))
			break ;
		else if (str[index] != ' ' && str[index] != '\t' &&
			str[index] != '<' && str[index] != '>' && str[index] != ';'
			&& str[index] != '&')
			eof[len++] = str[index];
		index++;
	}
	eof[len] = '\0';
	return (eof);
}

void	cursor_clear(t_counters t)
{
	int	index_line;
	int	max_line;

	index_line = ((t.index + t.diff_index) / tgetnum("co"));
	max_line = ((ft_intlen(t.str) + t.diff_index) / tgetnum("co"));
	while (index_line <= max_line)
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		index_line++;
	}
}

char	*norme_chokran_2(t_counters *t, struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
	return (t->tmp);
}

char	*ft_read_line(t_history **head, t_counters *t, char **env)
{
	char			buf[BUFF_SIZ + 1];
	static int		nb_nodes = 0;
	struct termios	term;

	engine_start(t, &term, head);
	while (1)
	{
		norme_chokran(t);
		t->ret = read(0, buf, BUFF_SIZ);
		buf[t->ret] = '\0';
		if (t->ret == 1 && buf[0] == 4)
			if (ft_ctrl_d(t, &nb_nodes, head))
				return (norme_chokran_2(t, &term));
		if (escape_or_not(t, buf, &nb_nodes, head))
			return (norme_chokran_2(t, &term));
		if (t->ret == 1 && buf[0] == '\t' && ft_intlen(t->str) == t->index)
			auto_complete(t, env);
		up_key(head, t, buf, nb_nodes);
		down_key(head, t, buf);
		calling_center(t, buf);
	}
	return (NULL);
}
