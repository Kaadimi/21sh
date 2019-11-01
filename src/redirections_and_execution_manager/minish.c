/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:11:19 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 18:36:47 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*give_serched(char *line, char c, t_nodes *start, int *in)
{
	char	*tmp[2];
	t_nodes	*head;

	head = NULL;
	ft_init(0, in, start, head);
	while (line[in[1]] != '\0')
	{
		if (line[in[1]] == 39)
			in[3]++;
		if (line[in[1]] == c && in[3] % 2 == 0)
		{
			tmp[0] = dollar_agent(in, line);
			if ((tmp[1] = verf_var(tmp[0], start)) != NULL)
				line = sar2(tmp[0], tmp[1], line, in);
			else if (dlr(line, tmp[0], head, start) < 0)
				return (NULL);
			ft_init(1, in, start, head);
		}
		in[1]++;
	}
	start = head;
	return (line);
}

t_nodes		*ft_aff_nodes(t_nodes *start, int i)
{
	t_nodes	*head;
	t_nodes	*trash;

	head = start;
	trash = NULL;
	ft_putstr("\x1b[0;36m>>Modified<<\x1b[0m");
	ft_putstr("   \x1b[0;34m>>Added<<\x1b[0m\n\n");
	while (start)
	{
		if (start->colrs == 'R')
		{
			start->next2 = NULL;
			if (i == 0)
				trash = start;
			if (i > 0)
				ft_env_add2(&trash, start);
		}
		else
			ft_aff_nodes_assi2(start->content, start->n_var, start->colrs);
		start = start->next;
		i++;
	}
	ft_aff_nodes_assi(trash);
	return (head);
}

t_nodes		*add_var_env(t_nodes **start, char **tmp1)
{
	t_nodes		*to_add;
	t_nodes		*head;

	if (args_check(tmp1) < 0)
		return (*start);
	if (add_var_assi(tmp1) == 0)
		return (*start);
	if (find_var(tmp1, *start) == 0)
	{
		head = *start;
		to_add = malloc(sizeof(t_nodes));
		to_add->n_var = ft_strnew(ft_strlen(tmp1[1]) + 1);
		if (tmp1[2] != NULL)
			to_add->content = ft_strnew(ft_strlen(tmp1[2] + 1));
		ft_strcat(to_add->n_var, tmp1[1]);
		if (tmp1[2] == NULL)
			to_add->content = NULL;
		else
			ft_strcat(to_add->content, tmp1[2]);
		to_add->sign = 'A';
		to_add->colrs = 'M';
		to_add->next = *start;
		*start = to_add;
	}
	return (*start);
}

int			find_var(char **tmp1, t_nodes *start)
{
	t_nodes		*head;

	head = start;
	while (start)
	{
		if (ft_strcmp(tmp1[1], start->n_var) == 0)
		{
			if (tmp1[2] != NULL)
				start->content = ft_strdup(tmp1[2]);
			else
				start->content = NULL;
			if (start->sign != 'A')
				start->sign = 'S';
			start->colrs = 'C';
			return (1);
		}
		start = start->next;
	}
	start = head;
	return (0);
}

char		*ft_get_home(void)
{
	struct passwd *pw;

	pw = getpwuid(getuid());
	return (pw->pw_dir);
}
