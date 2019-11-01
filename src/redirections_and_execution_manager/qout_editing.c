/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qout_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 17:50:53 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 18:36:39 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		remember_qout_sp(int i, char *res, char mode)
{
	if (mode == 'N')
	{
		if (res[i] == ' ')
			res[i] = -2;
		if (res[i] == '\t')
			res[i] = -3;
		return ;
	}
	if (res[i] == -2)
		res[i] = ' ';
	if (res[i] == -3)
		res[i] = '\t';
}

int			delete_qout_agent(char *vl, int i, char ch)
{
	while (vl[i] != ch)
	{
		remember_qout_sp(i, vl, 'R');
		i++;
	}
	return (i);
}

int			args_check(char **tmp1)
{
	if (!tmp1[1][0] || !tmp1[2][0])
	{
		ft_putstr_fd("Empty argements\n", 2);
		return (-1);
	}
	return (0);
}
