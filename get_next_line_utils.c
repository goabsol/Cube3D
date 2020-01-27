/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 22:10:56 by arhallab          #+#    #+#             */
/*   Updated: 2019/12/13 20:46:53 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		chrinstr(char *s, int c)
{
	int i;

	i = 0;
	if (s)
		while (s[i])
			if (s[i++] == c)
				return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	if (!(dup = (char*)malloc(sizeof(*dup) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int		ft_aprox_realloc(char **p, size_t size)
{
	char				*ptr;
	unsigned long long	i;

	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * size)))
		return (0);
	if (!(*p))
	{
		*p = ptr;
		return (1);
	}
	while ((*p)[i])
	{
		ptr[i] = (*p)[i];
		i++;
	}
	free(*p);
	*p = NULL;
	*p = ptr;
	return (1);
}
