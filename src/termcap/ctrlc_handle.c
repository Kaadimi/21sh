/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlc_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:53:00 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 20:05:45 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		signinthandler_2(char *cwd)
{
	t_counters	*c;
	char		**cmd;
	int			i;

	i = 0;
	c = getset(NULL);
	clear_quote(*c);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	if (!ft_strcmp(cwd, "/"))
	{
		ft_putstr("\e[1;96m/ ⇢ \e[0m");
		return ;
	}
	cmd = ft_strsplit(cwd, '/');
	while (cmd[i])
		i++;
	ft_putstr("\e[1;96m");
	ft_putstr(cmd[i - 1]);
	ft_putstr(" ⇢ \e[0m");
	struct_initialiser(c);
	c->diff_index = ft_intlen(cmd[i - 1]) + 3;
	tab_free(cmd);
}

void		siginthandler(int signal)
{
	char		cwd[255];

	if (signal == SIGINT)
	{
		if (g_wait == 0)
		{
			getcwd(cwd, 255);
			signinthandler_2(cwd);
		}
		else
			write(1, "\n", 1);
	}
}

t_counters	*getset(t_counters *t)
{
	static t_counters *c;

	if (t)
		c = t;
	return (c);
}

void		engine_start(t_counters *t, struct termios *term, t_history **head)
{
	t->start = *head;
	struct_initialiser(t);
	tcgetattr(STDIN_FILENO, term);
	set_input_mode();
	prompt_printer(t, 0);
}

void		norme_chokran(t_counters *t)
{
	t->bakara = 0;
	t->herdoc = 0;
	t->status = 0;
	signal(SIGINT, siginthandler);
}
