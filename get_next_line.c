/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 22:09:50 by arhallab          #+#    #+#             */
/*   Updated: 2019/12/05 08:50:13 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_flawed(int fd, char **line, unsigned long long *i, size_t lenk)
{
	unsigned long long	b;

	b = 0;
	while (!chrinstr(*line, '\n'))
	{
		if (!ft_aprox_realloc(line, sizeof(char) *
		((unsigned long long)BUFFER_SIZE *
		(*i + 1) + lenk + 1)))
			return (-1);
		(*i)++;
		b = read(fd, *line + BUFFER_SIZE * (*i - 1) +
			lenk, BUFFER_SIZE) + 1;
		if (!b--)
			return (-1);
		(*line)[BUFFER_SIZE * (*i - 1) + b + lenk] = '\0';
		if (b < BUFFER_SIZE && !chrinstr(*line, '\n'))
			return (0);
	}
	return (1);
}

static void	freekeep(char **keep)
{
	if (*keep)
	{
		**keep = 0;
		free(*keep);
		*keep = NULL;
	}
}

int			get_next_line(int fd, char **line)
{
	static char			*keep[1024];
	unsigned long long	i;
	unsigned long long	j;

	if (read(fd, NULL, 0) != 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	i = 0;
	if (!(*line = (keep[fd] ? ft_strdup(keep[fd]) : NULL)) && keep[fd])
		return (-1);
	j = read_flawed(fd, line, &i, (keep[fd] ? ft_strlen(keep[fd]) : 0)) + 1;
	if (j <= 1)
	{
		freekeep(&keep[fd]);
		return (j - 1);
	}
	j = 0;
	while ((*line)[j] != '\n' && j < BUFFER_SIZE
	* i + (keep[fd] ? ft_strlen(keep[fd]) : 0))
		j++;
	free(keep[fd]);
	if (!(keep[fd] = ft_strdup(*line + j + 1)) && *line + j + 1)
		return (-1);
	(*line)[j] = '\0';
	return (1);
}
