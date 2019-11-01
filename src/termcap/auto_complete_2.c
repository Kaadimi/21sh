/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:58:46 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 20:01:32 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tab_free(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
		ft_strdel(&tabs[i++]);
	free(tabs);
}

int		ft_start_compare(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	return (1);
}

char	*path_getter(char **path, char *str)
{
	DIR				*mydir;
	struct dirent	*myfile;
	int				i;

	i = 0;
	while (path[i])
	{
		mydir = opendir(path[i]);
		while ((myfile = readdir(mydir)))
			if (ft_start_compare(myfile->d_name, str))
			{
				closedir(mydir);
				return (myfile->d_name);
			}
		closedir(mydir);
		i++;
	}
	return (NULL);
}

int		path_counter(char **path, char *str)
{
	DIR				*mydir;
	struct dirent	*myfile;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (path[i])
	{
		mydir = opendir(path[i]);
		while ((myfile = readdir(mydir)))
			if (ft_start_compare(myfile->d_name, str))
				j++;
		closedir(mydir);
		i++;
	}
	return (j);
}

char	*ft_getpath(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_start_compare(env[i], "PATH="))
			path = env[i];
		i++;
	}
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i - 1] != '=')
		i++;
	return (my_strdup(path + i));
}
