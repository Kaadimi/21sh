/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_modifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:01:46 by ikadimi           #+#    #+#             */
/*   Updated: 2019/04/25 12:02:49 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_freejoin(char *s1, char *s2)
{
	char	*fr;
	size_t	v;

	if (!s1 || !s2)
		return (NULL);
	v = ft_strlen(s1) + ft_strlen(s2);
	fr = my_malloc(v + 1);
	ft_strcpy(fr, s1);
	ft_strcat(fr, s2);
	ft_strdel(&s1);
	s1 = NULL;
	return (fr);
}

char	*index_remover(char *str, int index)
{
	char	*new;
	int		i;

	if (index == 0 && ft_intlen(str) == 0)
		return (ft_strdup(""));
	else if (index > ft_intlen(str) || index < 0)
		return (NULL);
	i = -1;
	new = my_malloc(ft_intlen(str) + 1);
	while (++i < index)
		new[i] = str[i];
	while (str[++i])
		new[i - 1] = str[i];
	new[i - 1] = '\0';
	ft_strdel(&str);
	str = NULL;
	return (new);
}

char	*insert_char(char *str, char c, int index)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	new = my_malloc(ft_intlen(str) + 2);
	while (++i < index)
		new[i] = str[i];
	j = i;
	new[i++] = c;
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	ft_strdel(&str);
	return (new);
}

void	*my_malloc(size_t size)
{
	unsigned char	*zone;
	size_t			i;

	i = 0;
	if (!(zone = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		exit(0);
	while (i < size)
		zone[i++] = 0;
	return (zone);
}

char	*my_strdup(const char *s1)
{
	char	*s;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s = my_malloc(i + 1);
	i = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
