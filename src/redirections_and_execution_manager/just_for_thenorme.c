/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_for_thenorme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:27:04 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 16:00:59 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_mt_init(t_materials *mt, char **env, char **env_c)
{
	char	*oldpwd;

	oldpwd = NULL;
	mt->edited_command = NULL;
	mt->hrd_content = NULL;
	mt->tmp = NULL;
	mt->err = NULL;
	mt->oldpwd = getcwd(oldpwd, 255);
	mt->start = ft_env_gen(env_c);
	mt->head = NULL;
	mt->save = NULL;
	mt->save_env = NULL;
	mt->list = NULL;
	mt->pidnode = NULL;
	mt->env = env;
	mt->ops_c = NULL;
	mt->env_c = env_c;
	mt->is_pipe_exist = 0;
	mt->save_ior[0] = 0;
	mt->save_ior[1] = 0;
	mt->save_ior[2] = 0;
	mt->pipe_var[0] = 0;
	mt->pipe_var[1] = 0;
	mt->pid = 0;
	mt->save_inpipe = 0;
}

static int		get_right_index(char *cmd, int i)
{
	if (cmd[i] == '"')
	{
		i++;
		while (cmd[i] != '"')
			i++;
		i++;
		i = get_right_index(cmd, i);
	}
	if (cmd[i] == 39)
	{
		i++;
		while (cmd[i] != 39)
			i++;
		i++;
		i = get_right_index(cmd, i);
	}
	return (i);
}

static char		*checkcmd(char **cmd, char **hrd_content, char **edited_command)
{
	char	*tmp;

	tmp = cmd[0];
	cmd[0] = ft_strtrim(cmd[0]);
	ft_strdel(&tmp);
	if (ft_intlen(cmd[0]) == 0)
	{
		hrd_content[0] = NULL;
		edited_command[0] = NULL;
		return (NULL);
	}
	return ("DONE");
}

void			find_hrd_content(char *cmd, t_materials *mt)
{
	int		l;
	int		i;

	if (checkcmd(&cmd, &mt->hrd_content, &mt->edited_command) == NULL)
		return ;
	l = ft_intlen(cmd);
	i = 0;
	while (cmd[i])
	{
		i = get_right_index(cmd, i);
		if (cmd[i] == '\n')
		{
			l = i;
			while (cmd[i])
				i++;
			mt->hrd_content = ft_strsub(cmd, l, i - l);
			mt->edited_command = ft_strsub(cmd, 0, l);
			ft_strdel(&cmd);
			return ;
		}
		i++;
	}
	mt->hrd_content = NULL;
	mt->edited_command = ft_strsub(cmd, 0, l);
	ft_strdel(&cmd);
}

void			nd_minion_for_non_oprs(t_org *org, t_org *new_org, int *ops)
{
	if ((org->flags & OPR) == OPR)
	{
		if (ft_isnum(new_org->vl) == 1 &&
				((org->flags & DFD_AND_STDIN) == DFD_AND_STDIN
				|| (org->flags & RFD_OR_FILE) == RFD_OR_FILE))
		{
			new_org->flags = new_org->flags | FD_FOR_BEFORE_OPR;
		}
		else
		{
			new_org->vl = delete_qout(new_org->vl);
			new_org->flags = new_org->flags | FILE_FOR_OPR;
		}
	}
	else
	{
		ops[0]++;
		new_org->vl = delete_qout(new_org->vl);
		new_org->flags = new_org->flags | OPS_FOR_CMD;
	}
}
