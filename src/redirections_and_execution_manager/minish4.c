/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:13:16 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/05 17:12:10 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_free_nodes(t_nodes *start2)
{
	t_nodes		*start;

	if (!start2)
		return ;
	while (start2)
	{
		start = start2->next;
		if (start2->sign == 'A')
		{
			free(start2->n_var);
			free(start2->content);
		}
		else if (start2->sign == 'S')
			free(start2->content);
		free(start2);
		start2 = NULL;
		start2 = start;
	}
}

void		ft_cd(char **tmp0, char *oldpwd)
{
	char	*cwd;
	int		i;

	i = 1;
	cwd = NULL;
	while (tmp0[i])
		i++;
	if (i > 3)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (tmp0[1] == NULL)
		ft_go_home(oldpwd, cwd);
	else if (ft_strcmp("-", tmp0[1]) == 0)
	{
		if (ft_go_back(tmp0, cwd, oldpwd) == 0)
			return ;
	}
	else if (tmp0[1])
		if (ft_go_dir(tmp0, oldpwd) == 0)
			return ;
}

t_nodes		*rm_var_env(t_nodes **start, char **tmp1)
{
	int			i;
	t_nodes		*head;

	head = *start;
	i = 1;
	if (tmp1[1] == NULL)
	{
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
		return (*start);
	}
	while (*start)
	{
		i = 1;
		while (tmp1[i])
		{
			if ((*start)->n_var != NULL &&
				ft_strcmp(tmp1[i], (*start)->n_var) == 0)
				(*start)->colrs = 'R';
			i++;
		}
		(*start) = (*start)->next;
	}
	return (head);
}

char		*verf_var(char *to_find, t_nodes *start)
{
	while (start)
	{
		if (ft_strcmp(to_find, start->n_var) == 0)
			if (start->colrs != 'R')
				return (start->content);
		start = start->next;
	}
	return (NULL);
}

int			ft_go_back(char **tmp0, char *cwd, char *oldpwd)
{
	if (tmp0[2] != NULL)
	{
		ft_putstr_fd("cd: string not in pwd: -", 2);
		return (0);
	}
	cwd = ft_strdup(oldpwd);
	oldpwd = getcwd(oldpwd, 255);
	chdir(cwd);
	free(cwd);
	return (1);
}
