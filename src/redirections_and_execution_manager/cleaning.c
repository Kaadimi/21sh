/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:37:16 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 15:45:37 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_rlist(t_org *head)
{
	t_org	*save;

	if (!head)
		return ;
	while (head)
	{
		save = head->next;
		ft_strdel(&head->vl);
		free(head);
		head = NULL;
		head = save;
	}
}

void	free_t(char **ptr)
{
	int		i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0])
			ft_strdel(&ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	ft_del(void *data, size_t size)
{
	(void)size;
	ft_memdel(data);
}

void	cleaning(t_materials *mt)
{
	ft_free_nodes(mt->start);
	free_rlist(mt->head);
	ft_strdel(&mt->coped);
	free_t(mt->ops_c);
	repare_env_c(mt->env_c);
	free_t(mt->env_c);
	free_t(mt->pipe);
	free_t(mt->semi_colum);
	ft_strdel(&mt->hrd_content_lite);
	ft_strdel(&mt->hrd_content);
	ft_strdel(&mt->edited_command);
	ft_strdel(&mt->tmp);
}

void	ft_exit(t_materials *mt)
{
	cleaning(mt);
	exit(0);
}
