/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_and_helping_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:19:07 by ikadimi           #+#    #+#             */
/*   Updated: 2019/07/25 20:28:18 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	struct_initialiser(t_counters *t)
{
	static int	prog_status = 0;

	t->actions = 0;
	t->save = 0;
	t->error = 0;
	t->autoc = 0;
	t->str = my_strdup("");
	t->tmp = NULL;
	t->herdoc = 0;
	t->index = 0;
	t->back_up_index = 0;
	t->node_counter = 1;
	t->bakara = 0;
	t->quote = 0;
	t->diff_index = 0;
	t->inline_index = 0;
	t->status = 0;
	if (!prog_status)
		t->copy_str = NULL;
	prog_status = 1;
}

int		ft_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

void	set_input_mode(void)
{
	char			*term_name;
	struct termios	termios;

	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	term_name = getenv("TERM");
	if (!term_name)
		exit(-1);
	tgetent(NULL, term_name);
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

void	up_to_right(void)
{
	int	i;

	i = 1;
	tputs(tgetstr("up", NULL), 0, ft_outc);
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	while (i++ < tgetnum("co"))
		tputs(tgetstr("nd", NULL), 0, ft_outc);
}

void	edge_warden(t_counters *t, char *buf)
{
	int i;

	i = LINE;
	if (EDGE && (OUTPUT || INSERT || (RIGHT && t->bakara == 0)))
		tputs(tgetstr("do", NULL), 0, ft_outc);
	else if (((ft_intlen(t->str) + t->diff_index) % tgetnum("co")) == 0
	&& INSERT)
	{
		while (++i <= ((ft_intlen(t->str) + t->diff_index) / tgetnum("co")))
			tputs(tgetstr("do", NULL), 0, ft_outc);
		while (--i > LINE)
			tputs(tgetstr("up", NULL), 0, ft_outc);
		t->back_up_index = (t->index % tgetnum("co")) + t->diff_index;
		i = 0;
		while (i++ < t->back_up_index)
			tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	else if (((t->index + 1 + t->diff_index) % tgetnum("co")) == 0
	&& index > 0 && LEFT)
		up_to_right();
}
