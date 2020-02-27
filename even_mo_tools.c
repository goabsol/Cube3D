/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_mo_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:43:07 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/28 00:21:49 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		freetab(char **t)
{
	int	i;

	i = 0;
	while (t && t[i])
		free(t[i++]);
	free(t);
	return (1);
}

int		ps(char *str, t_g *g)
{
	if (!str)
		return (0);
	while (*str)
		write(2, (void *)str++, 1);
	freetab(g->m.a);
	free(g->sd);
	if (g->whotofree[0])
		free(g->l);
	if (g->whotofree[1])
		freetab(g->t);
	if (g->whotofree[2])
		freetab(g->tt);
	if (g->tb.animg)
		mlx_destroy_image(g->tb.p, g->tb.bi);
	return (1);
}

int		isnum(char *s)
{
	int		i;
	int		f1;
	int		f2;

	i = -1;
	f1 = 0;
	f2 = 0;
	while (s && s[++i])
	{
		if (s[i] == ' ' && !f1)
			continue ;
		if (!chrinstr(" 0123456789", s[i]) ||
		(f1 && f2 && chrinstr("0123456789", s[i])))
			return (0);
		if (chrinstr("0123456789", s[i]))
			f1 = 1;
		if (s[i] == ' ')
			f2 = 1;
	}
	return (1);
}

int		fnfree(char **l)
{
	free(*l);
	return (1);
}
