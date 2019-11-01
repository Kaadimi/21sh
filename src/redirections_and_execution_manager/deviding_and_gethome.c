/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviding_and_gethome.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:07:00 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 17:22:04 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*current_home(char *cmd, int *i)
{
	struct passwd	*pw;

	pw = getpwuid(getuid());
	cmd = find_replace(cmd, "~", pw->pw_dir);
	*i += ft_intlen(pw->pw_dir) - 1;
	return (cmd);
}

static void	return_j(int *j, char *cmd)
{
	if (cmd[j[0]] == '"')
	{
		j[0]++;
		while (cmd[j[0]] != '"')
			j[0]++;
		j[0]++;
	}
	else if (cmd[j[0]] == 39)
	{
		j[0]++;
		while (cmd[j[0]] != 39)
			j[0]++;
		j[0]++;
	}
	while (cmd[j[0]] != '\0' && cmd[j[0]] != ' ' && cmd[j[0]] != '\t')
		j[0]++;
}

static char	*other_home(char *cmd, int *j, int *i)
{
	char			*login;
	struct passwd	*pw;

	return_j(j, cmd);
	login = ft_strsub(cmd, i[0], j[0] - i[0]);
	login = delete_qout(login);
	if (!(pw = getpwnam(login)))
	{
		ft_putstr_fd("21sh: no such user or named directory: ", 2);
		ft_putendl_fd(login, 2);
		if (login)
			ft_strdel(&login);
		ft_strdel(&cmd);
		return (NULL);
	}
	else
	{
		free(login);
		login = ft_strsub(cmd, (i[0] - 1), j[0] - (i[0] - 1));
		cmd = find_replace(cmd, login, pw->pw_dir);
		i[0] += ft_intlen(pw->pw_dir);
	}
	return (cmd);
}

char		*ft_home2(char *cmd)
{
	int		i;
	int		j;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
	{
		i = ignore_quot(cmd, i);
		if (cmd[i] == '~' && (i += 1))
		{
			if (cmd[i] == '\0' || cmd[i] == ' ' || cmd[i] == '\t' ||
					cmd[i] == '\n' || cmd[i] == '/')
				cmd = current_home(cmd, &i);
			else if (cmd)
			{
				j = i;
				if ((cmd = other_home(cmd, &i, &j)) == NULL)
					return (NULL);
			}
		}
		if (!cmd[i])
			break ;
	}
	return (cmd);
}
