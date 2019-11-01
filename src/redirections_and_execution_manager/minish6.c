/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:18:14 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/04 15:18:55 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*d_h(char *line, t_nodes *start)
{
	char	*tmp5;
	char	*tmp2;
	t_nodes	*head;
	int		in[4];

	head = start;
	tmp2 = line;
	if (line != NULL)
	{
		if ((tmp5 = give_serched(tmp2, '$', start, in)) != NULL)
		{
			start = head;
			return (tmp5);
		}
		else
		{
			start = head;
			return (NULL);
		}
	}
	start = head;
	return (NULL);
}

char	*dollar_agent(int *in, char *line)
{
	in[2] = in[1] + 1;
	in[0] = in[1] + 1;
	while (ft_isalnum(line[in[0] + 1]))
		in[0]++;
	in[1] = in[2];
	return (replace_serched(line, in[0], in[2]));
}

int		dlr(char *line, char *tmp1, t_nodes *head, t_nodes *start)
{
	ft_putstr(tmp1);
	ft_putstr(": Undefined variable.\n");
	free(tmp1);
	free(line);
	start = head;
	ft_putstr(start->n_var);
	return (-1);
}

void	ft_init(int type, int *in, t_nodes *start, t_nodes *head)
{
	if (type == 0)
	{
		in[0] = 0;
		head = start;
		in[1] = 0;
		in[2] = 0;
		in[3] = 0;
	}
	else if (type == 1)
	{
		start = head;
		in[0] = 0;
		in[2] = 0;
	}
}

char	*sar2(char *tmp1, char *tmp2, char *line, int *in)
{
	line = sar(tmp1, tmp2, line, in[2] - 1);
	in[1] = 0;
	free(tmp1);
	tmp1 = NULL;
	return (line);
}
