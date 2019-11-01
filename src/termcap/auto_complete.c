/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 21:35:41 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 20:03:36 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*name_return_2(char *str, int index, int i)
{
	char	*name;
	int		j;

	j = 0;
	name = my_malloc(i + 1);
	while (str[index] != ' ' && str[index] != '\0' && str[index] != '\n')
		name[j++] = str[index++];
	name[j] = '\0';
	return (name);
}

char	*name_return(char *str)
{
	int		i;
	char	*name;
	int		len;

	len = 0;
	i = ft_intlen(str);
	while (str[i] != ' ' && str[i] != '\n' && i >= 0)
	{
		len++;
		i--;
	}
	if (len == 0)
		return (NULL);
	name = my_malloc(len);
	len = 0;
	i++;
	while (str[i] != '\0')
		name[len++] = str[i++];
	name[len] = '\0';
	return (name);
}

void	auto_complete_2(t_counters *t, int i, char **path, char *name)
{
	int		k;

	k = 0;
	if (i == 1)
	{
		home_button(t->index, t->diff_index);
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		t->str = string_mashup(t->str, path_getter(path, name));
		ft_putstr(t->str);
		t->index = ft_intlen(t->str);
	}
	else
	{
		tputs(tgetstr("do", NULL), 0, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
		while (k++ < ((t->index + t->diff_index) % tgetnum("co")))
			tputs(tgetstr("nd", NULL), 0, ft_outc);
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		t->autoc = 1;
		ft_putstr("\nFound ");
		ft_putnbr(i);
		ft_putstr(" Matches");
		tputs(tgetstr("rc", NULL), 0, ft_outc);
	}
}

int		auto_complete(t_counters *t, char **env)
{
	char	*paths;
	char	**path;
	char	*name;
	int		i;

	i = 0;
	name = name_return(t->str);
	if (name == NULL)
		return (0);
	paths = ft_getpath(env);
	if (paths == NULL)
		paths = my_strdup(":.");
	else
		paths = ft_freejoin(paths, ":.");
	path = ft_strsplit(paths, ':');
	ft_strdel(&paths);
	i = path_counter(path, name);
	auto_complete_2(t, i, path, name);
	ft_strdel(&name);
	tab_free(path);
	return (0);
}
