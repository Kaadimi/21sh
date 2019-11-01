/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preapre_for_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:05:09 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 15:50:39 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_org			*org_function(char *vl, t_org *org, int sign, int *ops)
{
	char	*tmp;

	if (sign == 0)
	{
		org = (t_org *)malloc(sizeof(t_org));
		if (vl[ft_strlen(vl) - 1] < 0)
			vl[ft_strlen(vl) - 1] += 127;
		tmp = ft_strdup(vl);
		org->vl = delete_qout(tmp);
		org->flags = 0;
		ops[0]++;
		org->flags = org->flags | CMD;
		org->next = NULL;
		org->prev = NULL;
		return (org);
	}
	else
		return (minions_manager(org, ops, vl));
	return (NULL);
}

static t_org	*flag_verification(t_org *tt, t_org *head, int mode)
{
	if (mode == 0)
	{
		if ((tt->flags & MENAS) == MENAS)
		{
			free_rlist(head);
			return (NULL);
		}
	}
	else if ((tt->flags & OPR) == OPR)
	{
		free_rlist(head);
		return (NULL);
	}
	return (head);
}

t_org			*ft_fill_list(char **test, int *ops)
{
	int		i;
	t_org	*tt;
	t_org	*head;

	i = 0;
	tt = NULL;
	head = NULL;
	while (test[i])
	{
		if (i == 0)
		{
			tt = org_function(test[i], tt, 0, ops);
			head = tt;
		}
		else
		{
			tt = org_function(test[i], tt, 1, ops);
			if (!flag_verification(tt, head, 0))
				return (NULL);
		}
		i++;
	}
	return (flag_verification(tt, head, 1));
}

char			**ft_ops_collector(t_org *head2, int *ops)
{
	char	**ops_c;
	int		i;

	ops_c = (char **)malloc(sizeof(char *) * (ops[0] + 1));
	ops_c[ops[0]] = NULL;
	i = 0;
	while (head2)
	{
		if ((head2->flags & OPS_FOR_CMD) == OPS_FOR_CMD
			|| (head2->flags & CMD) == CMD)
		{
			ops_c[i] = ft_strdup(head2->vl);
			i++;
		}
		head2 = head2->next;
	}
	return (ops_c);
}

t_org			*minions_manager(t_org *org, int *ops, char *vl)
{
	t_org	*new_org;
	int		i;

	new_org = (t_org *)malloc(sizeof(t_org));
	i = 0;
	while (vl[i++])
	{
		if (vl[i] == -2)
			vl[i] = ' ';
		if (vl[i] == -3)
			vl[i] = '\t';
	}
	new_org->vl = ft_strdup(vl);
	new_org->flags = 0;
	if (st_minion_for_oprs(org, new_org) == 0)
		if (nd_minion_for_oprs(org, new_org) == 0)
			if (rd_minion_for_oprs(org, new_org) == 0)
				if (th_minion_for_oprs(org, new_org) == 0)
					if (st_minion_for_non_oprs(org, new_org, ops) == 0)
						nd_minion_for_non_oprs(org, new_org, ops);
	new_org->next = NULL;
	org->next = new_org;
	new_org->prev = org;
	org = new_org;
	return (new_org);
}
