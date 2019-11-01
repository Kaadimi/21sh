/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:40:24 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/05 13:25:44 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		redis_assist(t_org *head, char *hrd_content)
{
	while (head)
	{
		if ((head->flags & OPR) == OPR)
		{
			if (head->vl[0] == '>' || head->vl[1] == '>')
			{
				if (redirection_output(head) < 0)
					return (-1);
				head = head->next;
			}
			else
			{
				if (redirection_input_hrd(head, hrd_content) < 0)
					return (-1);
				head = head->next;
			}
		}
		head = head->next;
	}
	return (0);
}

int		redirection_input_hrd(t_org *head, char *hrd_content)
{
	int		fd_after;
	int		fd_before;
	int		fds[2];

	fd_after = -1;
	fd_before = -1;
	if ((head->flags & RI) == RI
			|| (head->flags & DFD_AND_STDIN) == DFD_AND_STDIN)
	{
		if (redirection_input(head, fd_after, fd_before) < 0)
			return (-1);
	}
	else
	{
		pipe(fds);
		write(fds[1], hrd_content, ft_strlen(hrd_content));
		close(fds[1]);
		dup2(fds[0], 0);
	}
	return (0);
}

int		redirection_output(t_org *beguin)
{
	int		fd_after;
	int		fd_before;
	int		cls;

	fd_initializer(beguin, &fd_after, &fd_before, &cls);
	if (fd_before < 0)
	{
		if ((beguin->flags & RUT) == RUT || (beguin->flags & REU) == REU
				|| (beguin->flags & RFD_OR_FILE) == RFD_OR_FILE)
			fd_before = open(beguin->next->vl, O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IWUSR);
		if ((beguin->flags & RUA) == RUA)
			fd_before = open(beguin->next->vl, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR);
		if (fd_closing(beguin, fd_before, fd_after, &cls) < 0)
			return (-1);
	}
	if (fd_after < 0 && cls == 1)
		return (fd_duplicating1(beguin, fd_before));
	else if (cls == 1)
		return (fd_duplicating2(beguin, fd_before, fd_after));
	close(fd_before);
	return (0);
}

int		redirection_input(t_org *head, int fd_after, int fd_before)
{
	if ((head->next->flags & FILE_FOR_OPR) == FILE_FOR_OPR)
		fd_before = open(head->next->vl, O_RDONLY);
	else
		fd_before = ft_atoi(head->next->vl);
	if (fd_before < 0)
	{
		if (lstat(head->next->vl, NULL) != 0)
		{
			ft_putstr_fd("21sh: No such file or directory: ", 2);
			ft_putendl_fd(head->next->vl, 2);
			return (-1);
		}
		else if (access(head->next->vl, W_OK) < 0)
		{
			ft_putstr_fd("21sh: permission denied: ", 2);
			ft_putendl_fd(head->next->vl, 2);
			return (-1);
		}
	}
	return (redirecting_input(head, fd_after, fd_before));
}
