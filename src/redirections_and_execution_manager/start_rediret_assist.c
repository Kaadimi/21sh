/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rediret_assist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 22:07:05 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/05 13:26:20 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		redirecting_input(t_org *head, int fd_after, int fd_before)
{
	if ((head->prev->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR)
		fd_after = ft_atoi(head->prev->vl);
	if (fd_after >= 0)
	{
		if (dup2(fd_before, fd_after) < 0)
		{
			ft_putstr_fd("Error in dup2\n", 2);
			return (-1);
		}
	}
	else if (dup2(fd_before, 0) < 0)
	{
		ft_putstr_fd("Error in dup2\n", 2);
		return (-1);
	}
	close(fd_before);
	return (0);
}

int		fd_duplicating1(t_org *beguin, int fd_before)
{
	if ((beguin->flags & REU) == REU)
	{
		if (dup2(fd_before, 2) < 1)
		{
			ft_putstr_fd("Error in dup2\n", 2);
			return (-1);
		}
	}
	if (dup2(fd_before, 1) < 1)
	{
		ft_putstr_fd("Error in dup2\n", 2);
		return (-1);
	}
	return (0);
}

int		fd_duplicating2(t_org *beguin, int fd_before, int fd_after)
{
	if ((beguin->flags & REU) == REU)
	{
		if (dup2(fd_before, 2) < 1)
		{
			ft_putstr_fd("Error in dup2\n", 2);
			return (-1);
		}
	}
	if (dup2(fd_before, fd_after) < 1)
	{
		ft_putstr_fd("Error in dup2\n", 2);
		return (-1);
	}
	close(fd_before);
	return (0);
}

int		fd_closing(t_org *beguin, int fd_before, int fd_after, int *cls)
{
	if (beguin->next->vl[0] == '-' && !beguin->next->vl[1])
	{
		if (fd_after < 0)
			cls[0] = close(1);
		else
			cls[0] = close(fd_after);
		if (cls[0] < 0)
		{
			ft_putstr_fd("Error when closing: ", 2);
			ft_putendl_fd(beguin->next->vl, 2);
			return (-1);
		}
		return (0);
	}
	if (fd_before < 0)
	{
		if (access(beguin->next->vl, W_OK) < 0)
		{
			ft_putstr_fd("21sh: permission denied: ", 2);
			ft_putendl_fd(beguin->next->vl, 2);
			return (-1);
		}
	}
	return (0);
}

void	fd_initializer(t_org *beguin, int *fd_after, int *fd_before, int *cls)
{
	cls[0] = 1;
	fd_after[0] = -1;
	fd_before[0] = -1;
	if ((beguin->next->flags & FD_FOR_BEFORE_OPR) == FD_FOR_BEFORE_OPR)
		fd_before[0] = ft_atoi(beguin->next->vl);
	if ((beguin->prev->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR)
		fd_after[0] = ft_atoi(beguin->prev->vl);
}
