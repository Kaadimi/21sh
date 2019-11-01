/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_and_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:21:39 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 15:24:18 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_history		*create_list(char *command, int placement)
{
	t_history *new;

	new = (t_history *)malloc(sizeof(t_history));
	if (command)
		new->command = ft_strdup(command);
	new->placement = placement;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			node_to_list(t_history **list, t_history *node)
{
	node->next = *list;
	node->prev = NULL;
	if (*list != NULL)
		(*list)->prev = node;
	*list = node;
}

char			**env_copy(char **env)
{
	int		i;
	char	**env_c;

	i = 0;
	while (env[i])
		i++;
	env_c = (char **)malloc(sizeof(char *) * (i + 1));
	env_c[i] = NULL;
	i = 0;
	while (env[i])
	{
		env_c[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_c);
}

static void		check_execut_exit(t_materials *mt, t_counters *t, char *command)
{
	if (t->error == 0)
	{
		find_hrd_content(command, mt);
		if (mt->edited_command)
		{
			mt->edited_command = d_h(mt->edited_command, mt->start);
			mt->edited_command = ft_home2(mt->edited_command);
			if (mt->edited_command)
				executing_manager(mt);
		}
	}
}

int				main(int ac, char **av, char **env)
{
	char		*command;
	int			placement;
	t_materials	mt;
	t_counters	t;

	ft_mt_init(&mt, env, env_copy(env));
	placement = 0;
	getset(&t);
	while (1 || ac || av)
	{
		command = ft_read_line(&mt.history_head, &t, env);
		mt.coped = t.copy_str;
		if (placement == 0)
			mt.history_head = create_list(command, placement);
		else if (placement > 0)
		{
			mt.added = create_list(command, placement);
			node_to_list(&mt.history_head, mt.added);
		}
		check_execut_exit(&mt, &t, command);
		placement++;
	}
	return (0);
}
