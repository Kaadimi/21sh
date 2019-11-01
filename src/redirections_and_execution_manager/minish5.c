/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:16:40 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/04 15:17:41 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_go_dir(char **tmp0, char *oldpwd)
{
	oldpwd = getcwd(oldpwd, 255);
	if (chdir(tmp0[1]) == -1)
	{
		if (tmp0[2] != NULL)
		{
			ft_putstr_fd("cd: string not in pwd: ", 2);
			ft_putendl_fd(tmp0[1], 2);
		}
		else
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd(tmp0[1], 2);
		}
		return (0);
	}
	return (1);
}

void	ft_go_home(char *oldpwd, char *cwd)
{
	oldpwd = getcwd(oldpwd, 255);
	cwd = ft_get_home();
	chdir(cwd);
}

int		add_var_assi(char **tmp1)
{
	int		i;

	i = 1;
	while (tmp1[i] != NULL)
		i++;
	if (i > 3)
	{
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
		return (0);
	}
	return (1);
}

void	ft_aff_nodes_assi(t_nodes *trash)
{
	ft_putstr("                   \x1b[0;35m>>Trash<<\x1b[0m\n");
	if (trash == NULL)
		ft_putstr("\x1b[0;31m>>Empty<<\x1b[0m\n");
	while (trash)
	{
		ft_putstr("\x1b[0;31m");
		ft_putstr(trash->n_var);
		if (trash->n_var != NULL)
			ft_putchar('=');
		if (trash->content == NULL && trash->n_var != NULL)
			ft_putchar('\n');
		else
			ft_putendl(trash->content);
		ft_putstr("\x1b[0m");
		trash = trash->next2;
	}
}

void	ft_aff_nodes_assi2(char *content, char *n_var, char colrs)
{
	if (colrs == 'C')
	{
		ft_putstr("\x1b[0;36m");
		ft_putstr(n_var);
		ft_putstr("\x1b[0m");
	}
	else if (colrs == 'M')
	{
		ft_putstr("\x1b[0;34m");
		ft_putstr(n_var);
		ft_putstr("\x1b[0m");
	}
	else
		ft_putstr(n_var);
	if (n_var != NULL)
		ft_putchar('=');
	if (content == NULL && n_var != NULL)
		ft_putchar('\n');
	else
		ft_putendl(content);
}
