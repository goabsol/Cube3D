/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_mo_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:43:07 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/28 23:21:41 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		freetab(char ***t)
{
	int	i;

	i = 0;
	while (*t && (*t)[i])
		free((*t)[i++]);
	if (*t)
	{
		free(*t);
		*t = NULL;
	}
	return (1);
}

int		ps(char *str, t_g *g)
{
	if (!str)
		return (0);
	while (*str)
		write(2, (void *)str++, 1);
	freetab(&(g->m.a));
	free(g->sd);
	g->whotofree[0] ? free(g->l) : 0;
	g->whotofree[1] ? freetab(&(g->t)) : 0;
	g->whotofree[2] ? freetab(&(g->tt)) : 0;
	g->tb.animg ? mlx_destroy_image(g->tb.p, g->tb.bi) : 0;
	g->tb.aw ? mlx_destroy_window(g->tb.p, g->tb.w) : 0;
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

void	check_args(int a, char **b, t_g *g)
{
	a != 2 && a != 3 ? exit(ps(ARG, g)) : 0;
	if (a == 3)
		!ft_strcmp(b[2], "--save") ? g->save = 1 : exit(ps(WA, g));
	if (a == 2)
		!ft_strcmp(b[1] + ft_strlen(b[1]) - 4, ".cub") ? 0 : exit(ps(WA, g));
}
