/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmamouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 20:38:44 by mmamouni          #+#    #+#             */
/*   Updated: 2019/08/16 15:24:54 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	prepare_for_redis_and_pipe(t_materials *mt, char *res)
{
	res = ft_prepare(mt->av);
	mt->tmp = res;
	res = ft_strtrim(res);
	ft_strdel(&mt->tmp);
	mt->test = ft_split(res);
	ft_strdel(&res);
	mt->save_env = mt->start;
	mt->head = ft_fill_list(mt->test, mt->ops);
	free_t(mt->test);
	mt->save = mt->head;
	if (!mt->head)
	{
		ft_putstr_fd("Syntax Error\n", 2);
		return (-1);
	}
	dup2(mt->save_inpipe, 0);
	close(mt->save_inpipe);
	if (mt->is_pipe_exist == 1)
	{
		pipe(mt->pipe_var);
		dup2(mt->pipe_var[1], 1);
		close(mt->pipe_var[1]);
		mt->save_inpipe = mt->pipe_var[0];
	}
	return (0);
}

static int	redirect_execute_exit(t_materials *mt, t_list **node)
{
	if ((mt->pid = fork()) == 0)
	{
		if (execve(mt->tmp, mt->ops_c, mt->env) < 0)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(mt->tmp, 2);
			return (-1);
		}
		exit(0);
	}
	*node = ft_lstnew(NULL, 0);
	mt->pidnode = malloc(sizeof(t_pids));
	mt->pidnode->pid = mt->pid;
	mt->pidnode->wait = 1;
	(*node)->content = mt->pidnode;
	ft_lstadd(&mt->list, *node);
	return (0);
}

int			redirect_and_execute(t_materials *mt)
{
	t_list	*node;
	char	*res;
	int		i;

	res = NULL;
	mt->ops[0] = 0;
	if (prepare_for_redis_and_pipe(mt, res) < 0)
		return (-1);
	mt->hrd_content_lite = get_hrd_content(mt->save, &mt->hrd_content);
	mt->ops_c = ft_ops_collector(mt->head, mt->ops);
	str_to_lower(&mt->ops_c[0]);
	if (redis_assist(mt->head, mt->hrd_content_lite) == -1)
		return (-1);
	if (ft_strcmp("exit", mt->ops_c[0]) == 0)
		ft_exit(mt);
	i = t_cmd(mt->ops_c, &mt->start, mt->oldpwd, mt);
	if (i == -1)
		return (-1);
	if (i == 0)
		return (0);
	mt->start = mt->save_env;
	return (redirect_execute_exit(mt, &node));
}
