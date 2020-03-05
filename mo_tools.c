/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mo_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:26:42 by arhallab          #+#    #+#             */
/*   Updated: 2020/03/04 22:56:08 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		ocins(char *c, const char *s)
{
	int	i;
	int	j;
	int	o;

	i = -1;
	o = 0;
	while (s[++i] && (j = -1))
		if (!chrinstr(c, s[i]))
			return (1);
	return (0);
}

int		ft_realloc(void ***p, size_t size, size_t so)
{
	void				**ptr;
	unsigned long long	i;

	i = 0;
	if (!(ptr = malloc(size * so)))
		return (0);
	if (!(*p))
	{
		*p = ptr;
		while (i < size)
			ptr[i++] = NULL;
		return (1);
	}
	while ((*p)[i])
	{
		ptr[i] = (*p)[i];
		i++;
	}
	while (i < size)
		ptr[i++] = NULL;
	free(*p);
	*p = ptr;
	return (1);
}

int		t_s_array_realloc(t_s **p, size_t size)
{
	t_s					*ptr;
	unsigned long long	i;

	i = 0;
	if (!(ptr = malloc(sizeof(t_s) * size)))
		return (0);
	if (!(*p))
	{
		*p = ptr;
		return (1);
	}
	while (i < size - 1)
	{
		ptr[i] = (*p)[i];
		i++;
	}
	free(*p);
	*p = ptr;
	return (1);
}

void	sprite_rsort(t_s **a, int s)
{
	int		i;
	int		j;
	t_s		tmp;

	i = -1;
	while (++i < s)
	{
		j = i;
		while (++j < s)
		{
			if ((*a)[i].dst < (*a)[j].dst)
			{
				tmp = (*a)[i];
				(*a)[i] = (*a)[j];
				(*a)[j] = tmp;
			}
		}
	}
}

char	*strdup_spe(char *s, char c)
{
	char	*dup;
	size_t	i;
	size_t	j;
	size_t	u;

	i = 0;
	u = 0;
	j = 0;
	while (s[i] || (i = 0))
		if (s[i++] == c)
			u++;
	if (!(dup = (char*)malloc(sizeof(*dup) * (ft_strlen(s) + 1 - u))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
			dup[j++] = s[i];
		i++;
	}
	dup[j] = '\0';
	return (dup);
}
