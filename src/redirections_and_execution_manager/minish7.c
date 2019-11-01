/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:19:40 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 17:33:16 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*replace_serched(char *line, int l, int k)
{
	int		i;
	char	*tmp3;

	tmp3 = NULL;
	if (l != 0)
	{
		tmp3 = (char *)malloc(sizeof(char) * l);
		tmp3[l] = '\0';
		i = 0;
		while (k <= l)
		{
			tmp3[i] = line[k];
			i++;
			k++;
		}
		tmp3[i] = '\0';
	}
	return (tmp3);
}

char		*sar(char *serched, char *replaced, char *modified, int k)
{
	int		in[4];
	char	*tmp;

	in[0] = ft_strlen(modified) + ft_strlen(replaced) - ft_strlen(serched);
	tmp = (char *)malloc(sizeof(char) * in[0]);
	in[1] = in[0];
	in[0] = 0;
	in[2] = 0;
	in[3] = 0;
	while (in[0] < in[1])
	{
		if (in[0] == k)
		{
			while (replaced[in[2]] != '\0')
				tmp[in[0]++] = replaced[in[2]++];
			if (ft_strlen(serched) == 1)
				in[3] = in[3] + ft_strlen(serched);
			else
				in[3] = in[3] + 1 + ft_strlen(serched);
		}
		tmp[in[0]++] = modified[in[3]++];
	}
	free(modified);
	tmp[in[0] + 1] = '\0';
	return (tmp);
}

void		ft_echo(char **line)
{
	int		i;
	int		nflag;

	i = 1;
	nflag = 0;
	if (ft_strequ(line[1], "-n") && (nflag = 1))
		i++;
	while (line[i])
	{
		ft_putstr(line[i]);
		if (line[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!nflag)
		ft_putchar('\n');
}

void		ft_env_add2(t_nodes **start, t_nodes *new)
{
	new->next2 = *start;
	*start = new;
}

void		ft_replace(char *s1, char c)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\t' || s1[i] == ' ')
			s1[i] = c;
		i++;
	}
}
