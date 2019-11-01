/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_special_mash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:01:59 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 20:02:45 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	term_putstr(char *str, int index)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		index++;
		if (((index) % tgetnum("co")) == 0 && index > 0)
			tputs(tgetstr("do", NULL), 0, ft_outc);
	}
}

void	q_term_putstr(char *str, int index)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		index++;
		if (((index) % tgetnum("co")) == 0 && str[i] == '\n')
			tputs(tgetstr("do", NULL), 0, ft_outc);
	}
}

int		str_len(char *str)
{
	int		i;
	int		len;

	len = 0;
	i = ft_intlen(str);
	while (str[i] != ' ' && str[i] != '\n' && i > 0)
	{
		len++;
		i--;
	}
	if (i == 0)
		len++;
	return (len);
}

char	*string_mashup(char *str1, char *str2)
{
	int		i;
	char	*new;
	int		j;

	j = str_len(str1);
	if (j >= ft_intlen(str1))
	{
		ft_strdel(&str1);
		new = my_strdup(str2);
		return (new);
	}
	i = ft_intlen(str1) + ft_intlen(str2) - j;
	new = my_malloc(i + 1);
	i = 0;
	while (i <= (ft_intlen(str1) - j))
	{
		new[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
		new[i++] = str2[j++];
	new[i] = '\0';
	ft_strdel(&str1);
	return (new);
}

bool	space_before(t_counters t)
{
	int i;

	i = 0;
	while (i < t.index)
		if (t.str[i++] == ' ')
			return (true);
	return (false);
}
