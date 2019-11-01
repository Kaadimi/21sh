/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semi_solum_and_pipe.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:49:14 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 17:20:08 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			verif_pipe(char *cmd)
{
	int		i;
	char	*tmp;
	char	**pipe;

	i = 0;
	if (cmd[0] == '|' || cmd[ft_strlen(cmd) - 1] == '|')
		return (-1);
	pipe = pipe_function(&cmd);
	tmp = NULL;
	while (pipe[i])
	{
		tmp = ft_strtrim(pipe[i]);
		if (ft_strlen(tmp) == 0)
		{
			free_t(pipe);
			ft_strdel(&tmp);
			return (-1);
		}
		ft_strdel(&tmp);
		i++;
	}
	free_t(pipe);
	return (0);
}

int			verif_semi_colum(char **semi_colum)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (semi_colum[i])
	{
		tmp = ft_strtrim(semi_colum[i]);
		if (ft_strlen(tmp) == 0 || verif_pipe(tmp) < 0)
		{
			ft_putstr_fd("Syntax error\n", 2);
			ft_strdel(&tmp);
			return (-1);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

int			check_semi_colum(t_materials *mt)
{
	if (verif_semi_colum(mt->semi_colum) < 0)
	{
		if (mt->hrd_content)
			ft_strdel(&mt->hrd_content);
		free_t(mt->semi_colum);
		mt->semi_colum = NULL;
		return (-1);
	}
	return (0);
}

char		**semi_colum_function(char **full_cmd)
{
	int		i;
	char	**sume_colum;

	i = 0;
	while (full_cmd[0][i])
	{
		i = ignore_quot(full_cmd[0], i);
		if (full_cmd[0][i] == ';')
			full_cmd[0][i] = -1;
		i++;
	}
	i = 0;
	while (full_cmd[0][i])
	{
		if (full_cmd[0][i] == -2)
			full_cmd[0][i] = ' ';
		if (full_cmd[0][i] == -3)
			full_cmd[0][i] = '\t';
		i++;
	}
	sume_colum = ft_strsplit(full_cmd[0], -1);
	ft_strdel(full_cmd);
	return (sume_colum);
}

char		**pipe_function(char **cmd)
{
	int		i;
	char	**pipe;

	i = 0;
	while (cmd[0][i])
	{
		i = ignore_quot(cmd[0], i);
		if (cmd[0][i] == '|' && cmd[0][i + 1] != '|' && cmd[0][i - 1] != '|')
			cmd[0][i] = -1;
		i++;
	}
	pipe = ft_strsplit(cmd[0], -1);
	return (pipe);
}
