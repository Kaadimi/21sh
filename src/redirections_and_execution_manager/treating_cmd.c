/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_for_thenorme2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:33:21 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 17:51:33 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_builtin(t_materials *mt, char **tmp1)
{
	if (mt->tmp == NULL)
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(tmp1[0], 2);
		return (-1);
	}
	else if (access(&mt->tmp[0], X_OK) < 0)
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putendl_fd(tmp1[0], 2);
		return (-1);
	}
	return (1);
}

void		null(t_org **head, char ***ops_c, char **hr, char **tmp)
{
	free_rlist(*head);
	free_t(*ops_c);
	if (hr[0])
		ft_strdel(hr);
	ft_strdel(tmp);
	*head = NULL;
	*ops_c = NULL;
}

int			t_cmd(char **tmp1, t_nodes **start, char *oldpwd, t_materials *mt)
{
	int		i;
	t_nodes	*start2;

	start2 = *start;
	i = 0;
	if (ft_strcmp(tmp1[0], "setenv") == 0 && tmp1[1] != NULL)
		*start = add_var_env(start, tmp1);
	else if (ft_strcmp(tmp1[0], "setenv") == 0 && tmp1[1] == NULL)
		*start = ft_aff_nodes(*start, i);
	else if (ft_strcmp(tmp1[0], "unsetenv") == 0)
		*start = rm_var_env(start, tmp1);
	else if (!ft_strcmp(tmp1[0], "env") ||
			!ft_strcmp(tmp1[0], "/usr/bin/env"))
		*start = ft_aff_nodes(*start, i);
	else if (ft_strcmp("echo", tmp1[0]) == 0)
		ft_echo(tmp1);
	else if (ft_strcmp("cd", tmp1[0]) == 0)
		ft_cd(tmp1, oldpwd);
	else if ((mt->tmp = verf_cmd(tmp1[0], *start)) == NULL || 1)
		return (ft_builtin(mt, tmp1));
	return (0);
}

int			th_minion_for_oprs(t_org *org, t_org *new_org)
{
	if (!ft_strcmp(new_org->vl, "<&"))
	{
		new_org->flags = new_org->flags | DFD_AND_STDIN;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	return (0);
}
