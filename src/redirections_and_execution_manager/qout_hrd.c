/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qout_hrd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:03:34 by mmostafa          #+#    #+#             */
/*   Updated: 2019/08/16 17:38:57 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			find_index_to_insert_sp(char **res, int i)
{
	int		k;

	if (res[0][i - 1] != ' ' && i != 0)
	{
		res[0] = insert_char(res[0], ' ', i);
		res[0][i - 1] = res[0][i - 1] - 127;
		i++;
	}
	k = 0;
	while ((res[0][i] == '>' || res[0][i] == '<' || res[0][i] == '&')
			&& res[0][i] != '\0')
	{
		i++;
		k++;
		if (k == 2)
			break ;
	}
	return (i);
}

int			ignore_quot(char *res, int i)
{
	if (res[i] == '"' && (i += 1))
	{
		while (res[i] != '"')
		{
			remember_qout_sp(i, res, 'N');
			i++;
		}
		i++;
		i = ignore_quot(res, i);
	}
	if (res[i] == 39 && (i += 1))
	{
		while (res[i] != 39)
		{
			remember_qout_sp(i, res, 'N');
			i++;
		}
		i++;
		i = ignore_quot(res, i);
	}
	return (i);
}

static char	*get_line_in_str2(char *str)
{
	int		l;
	int		start;

	start = 0;
	if (str[start] == '\n')
		start++;
	l = start;
	if (str[start] == '\0')
		return (NULL);
	while (str[l] != '\0' && str[l] != '\n')
		l++;
	return (ft_strsub(str, start, l - start));
}

static char	*hrd_without_end(t_org *head, char **hrd_content, char *hrd)
{
	char	*tmp;

	while (head)
	{
		if ((head->flags & HRD) == HRD)
		{
			while ((tmp = get_line_in_str2(hrd_content[0])) != NULL)
			{
				if (ft_strcmp(tmp, head->next->vl) == 0)
				{
					hrd_content[0] = mini_remove_strinstr(hrd_content[0],
						(ft_intlen(tmp) + 1), 0);
					ft_strdel(&tmp);
					break ;
				}
				hrd = ft_freejoin(ft_freejoin(hrd, "\n"), tmp);
				hrd_content[0] = mini_remove_strinstr(hrd_content[0],
						(ft_intlen(tmp) + 1), 0);
				ft_strdel(&tmp);
			}
			head = head->next;
		}
		head = head->next;
	}
	return (hrd);
}

char		*get_hrd_content(t_org *head, char **hrd_content)
{
	char	*tmp;
	char	*hrd;

	if (!hrd_content[0])
		return (NULL);
	tmp = NULL;
	hrd = ft_strnew(0);
	if (hrd_content[0][0] == '\n')
		hrd_content[0] = index_remover(hrd_content[0], 0);
	hrd = hrd_without_end(head, hrd_content, hrd);
	if (hrd[0] == '\n')
		hrd = index_remover(hrd, 0);
	if (hrd[0])
		hrd = insert_char(hrd, '\n', ft_intlen(hrd));
	return (hrd);
}
