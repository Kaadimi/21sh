/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_functions_minions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 09:34:25 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 16:50:34 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		set_reset_std_ior(int mode, t_materials *mt)
{
	if (mode == 1)
	{
		mt->save_ior[0] = dup(0);
		mt->save_ior[1] = dup(1);
		mt->save_ior[2] = dup(2);
		mt->save_inpipe = dup(0);
	}
	if (mode == 0)
	{
		dup2(mt->save_ior[0], 0);
		dup2(mt->save_ior[1], 1);
		dup2(mt->save_ior[2], 2);
		close(mt->save_ior[0]);
		close(mt->save_ior[2]);
		close(mt->save_ior[1]);
	}
}

static void		executing_piping(t_materials *mt, int l)
{
	while (mt->pipe[++l])
	{
		if (mt->pipe[1])
			mt->is_pipe_exist = 1;
		if (!mt->pipe[l + 1])
		{
			dup2(mt->save_ior[1], 1);
			dup2(mt->save_ior[2], 2);
			mt->is_pipe_exist = 0;
		}
		mt->av = mt->pipe[l];
		if (redirect_and_execute(mt) < 0)
		{
			null(&mt->head, &mt->ops_c, &mt->hrd_content_lite, &mt->tmp);
			break ;
		}
		null(&mt->head, &mt->ops_c, &mt->hrd_content_lite, &mt->tmp);
	}
}

static void		waiting_killing(t_materials *mt)
{
	t_pids	*pid;
	t_list	*head;
	int		j;

	head = mt->list;
	j = 0;
	while (mt->list)
	{
		pid = mt->list->content;
		if (j == 0)
		{
			g_wait = 1;
			waitpid(pid->pid, 0, 0);
			g_wait = 0;
		}
		mt->list = mt->list->next;
		j++;
	}
	while (head)
	{
		pid = head->content;
		kill(pid->pid, 9);
		head = head->next;
	}
}

static void		freeing(t_list *free_tmp)
{
	t_list	*tmp;

	while (free_tmp)
	{
		tmp = free_tmp->next;
		free(free_tmp->content);
		free(free_tmp);
		free_tmp = tmp;
	}
}

void			executing_manager(t_materials *mt)
{
	int		i;
	int		l;
	t_list	*free_tmp;

	mt->list = NULL;
	i = -1;
	mt->semi_colum = semi_colum_function(&mt->edited_command);
	if (check_semi_colum(mt) < 0)
		return ;
	while (mt->semi_colum[++i])
	{
		set_reset_std_ior(1, mt);
		mt->pipe = pipe_function(&mt->semi_colum[i]);
		l = -1;
		executing_piping(mt, l);
		free_t(mt->pipe);
		free_tmp = mt->list;
		waiting_killing(mt);
		freeing(free_tmp);
		set_reset_std_ior(0, mt);
	}
	free_t(mt->semi_colum);
	mt->semi_colum = NULL;
}
