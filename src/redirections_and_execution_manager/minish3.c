/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:03:59 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/05 13:35:48 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_nodes		*ft_env_gen(char **env)
{
	t_nodes		*start;
	t_nodes		*next;
	int			i;

	i = 0;
	while (env[i] != NULL)
	{
		next = malloc(sizeof(t_nodes));
		next->n_var = env[i];
		next->content = ft_strstr(env[i], "=");
		(*next->content) = '\0';
		next->content++;
		next->sign = '0';
		next->colrs = '0';
		next->next = NULL;
		if (i == 0)
			start = next;
		if (i > 0)
			ft_env_add(&start, next);
		i++;
	}
	return (start);
}

void		ft_env_add(t_nodes **start, t_nodes *new)
{
	new->next = *start;
	*start = new;
}

void		ft_free2(char **tmp1)
{
	int		i;

	i = 0;
	while (tmp1[i] != NULL)
	{
		free(tmp1[i]);
		tmp1[i] = NULL;
		i++;
	}
	free(tmp1);
	tmp1 = NULL;
}

void		str_to_lower(char **str)
{
	int		i;

	i = 0;
	while (str[0][i])
	{
		str[0][i] = ft_tolower(str[0][i]);
		i++;
	}
}
