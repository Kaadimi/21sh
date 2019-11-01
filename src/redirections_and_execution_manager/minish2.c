/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:01:21 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 15:36:17 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*verf_cmd(char *tmp1, t_nodes *start)
{
	int			i;
	t_nodes		*head;
	t_nodes		*head2;
	struct stat	infos;

	i = 0;
	head2 = start;
	if (!tmp1[0])
		return (tmp1);
	if (tmp1[0] == '/')
		if (lstat(tmp1, &infos) == 0)
			return (ft_strdup(tmp1));
	while (start)
	{
		if (ft_strcmp("PATH", start->n_var) == 0)
		{
			head = start;
			start = head2;
			return (verf_cmd_ass(head->content, tmp1, head->colrs));
		}
		start = start->next;
	}
	start = head2;
	return (NULL);
}

char	*verf_cmd_ass(char *content, char *tmp1, char colrs)
{
	char	**tmp6;
	char	*tmp9;

	if (content == NULL || colrs == 'R')
		return (NULL);
	tmp6 = ft_strsplit(content, ':');
	if ((tmp9 = search_in_path2(tmp1, tmp6)) == NULL)
	{
		ft_free2(tmp6);
		return (0);
	}
	else
	{
		ft_free2(tmp6);
		return (tmp9);
	}
	return (0);
}

char	*search_in_path2(char *tmp1, char **tmp6)
{
	int		in[2];
	char	*tmp[2];

	in[1] = ft_strlen(tmp1);
	while (in[1] > 0)
	{
		if (tmp1[in[1]] == '/')
		{
			tmp1[in[1]] = '\0';
			break ;
		}
		in[1]--;
	}
	in[0] = 0;
	while (tmp6[in[0]])
	{
		if (ft_strcmp(tmp1, tmp6[in[0]]) == 0 && search_assist2(tmp1, in))
			return (ft_strdup(tmp1));
		else if (in[1] == 0 && (tmp[0] = search_assi(tmp, tmp1, tmp6, in)))
			return (tmp[0]);
		in[0]++;
	}
	if (in[1] != 0)
		tmp1[in[1]] = '/';
	return (NULL);
}

char	*search_assi(char **tmp, char *tmp1, char **tmp6, int *in)
{
	struct stat		infos;

	tmp[1] = ft_strjoin(tmp6[in[0]], "/");
	tmp[0] = ft_strjoin(tmp[1], tmp1);
	if (lstat(tmp[0], &infos) == 0)
	{
		free(tmp[1]);
		return (tmp[0]);
	}
	free(tmp[1]);
	free(tmp[0]);
	return (NULL);
}

int		search_assist2(char *tmp1, int *in)
{
	struct stat infos;

	tmp1[in[1]] = '/';
	if (lstat(tmp1, &infos) == 0)
		return (1);
	return (0);
}
