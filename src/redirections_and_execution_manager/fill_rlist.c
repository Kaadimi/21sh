/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:32:37 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 13:21:22 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			st_minion_for_oprs(t_org *org, t_org *new_org)
{
	if (!ft_strcmp(new_org->vl, ">"))
	{
		new_org->flags = new_org->flags | RUT;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	if (!ft_strcmp(new_org->vl, ">>"))
	{
		new_org->flags = new_org->flags | RUA;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	return (0);
}

int			nd_minion_for_oprs(t_org *org, t_org *new_org)
{
	if (!ft_strcmp(new_org->vl, "<"))
	{
		new_org->flags = new_org->flags | RI;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	if (!ft_strcmp(new_org->vl, "<<"))
	{
		new_org->flags = new_org->flags | HRD;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	return (0);
}

int			rd_minion_for_oprs(t_org *org, t_org *new_org)
{
	if (!ft_strcmp(new_org->vl, "&>"))
	{
		new_org->flags = new_org->flags | REU;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	if (!ft_strcmp(new_org->vl, ">&"))
	{
		new_org->flags = new_org->flags | RFD_OR_FILE;
		new_org->flags = new_org->flags | OPR;
		if ((org->flags & OPR) == OPR)
			new_org->flags = new_org->flags | MENAS;
		else if ((org->flags & S_CASE) == S_CASE)
			if ((org->flags & FD_FOR_AFTER_OPR) == FD_FOR_AFTER_OPR
					&& (org->prev->flags & OPR) == OPR)
				new_org->flags = new_org->flags | MENAS;
		return (1);
	}
	return (0);
}

static void	check_flag(t_org *org, t_org *new_org)
{
	if (new_org->vl[0] && ft_isnum(new_org->vl) == 1 &&
			((org->flags & DFD_AND_STDIN) == DFD_AND_STDIN
			|| (org->flags & RFD_OR_FILE) == RFD_OR_FILE))
	{
		new_org->flags = new_org->flags | FD_FOR_BEFORE_OPR;
	}
	else
		new_org->flags = new_org->flags | FILE_FOR_OPR;
}

int			st_minion_for_non_oprs(t_org *org, t_org *new_org, int *ops)
{
	int		i;

	i = 0;
	if ((i = search_in_str(new_org->vl)) >= 0)
	{
		new_org->vl[i] += 127;
		new_org->vl = delete_qout(new_org->vl);
		new_org->flags = new_org->flags | S_CASE;
		if (ft_strlen(new_org->vl) == 1 && (new_org->vl[0] >= '0'
					&& new_org->vl[0] <= '9'))
			new_org->flags = new_org->flags | FD_FOR_AFTER_OPR;
		else if ((org->flags & OPR) == OPR)
			check_flag(org, new_org);
		else
		{
			ops[0]++;
			new_org->vl = delete_qout(new_org->vl);
			new_org->flags = new_org->flags | OPS_FOR_CMD;
		}
		return (1);
	}
	return (0);
}
