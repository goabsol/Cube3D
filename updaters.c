/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:37:09 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/28 22:56:32 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int			kp(int k, t_g *g)
{
	if (k == 13)
		g->p.w[0] = 1;
	else if (k == 1)
		g->p.w[1] = 1;
	else if (k == 2)
		g->p.w[2] = 1;
	else if (!k)
		g->p.w[3] = 1;
	else if (k == 124)
		g->p.t[0] = 1;
	else if (k == 123)
		g->p.t[1] = 1;
	else if (k == 53)
		exit(ps("", g));
	return (1);
}

int			kr(int k, t_g *g)
{
	if (k == 13)
		g->p.w[0] = 0;
	if (k == 1)
		g->p.w[1] = 0;
	if (k == 2)
		g->p.w[2] = 0;
	if (!k)
		g->p.w[3] = 0;
	if (k == 124)
		g->p.t[0] = 0;
	if (k == 123)
		g->p.t[1] = 0;
	return (1);
}

static void	collditions(t_g *g, double *tmp)
{
	int				i;

	i = -g->p.s / 2;
	while (++i < g->p.s / 2)
	{
		if (g->m.a[((int)tmp[1] - g->p.s / 2 + 1 + i) / g->m.ts]
		[((int)g->p.p[0] - g->p.s / 2 + 1) / g->m.ts] != '0' ||
		g->m.a[((int)tmp[1] - g->p.s / 2 + 1) / g->m.ts]
		[((int)g->p.p[0] + i - g->p.s / 2 + 1) / g->m.ts] != '0' ||
		g->m.a[((int)tmp[1] - g->p.s / 2 + 1 + i) / g->m.ts]
		[((int)g->p.p[0] + g->p.s / 2 - 1) / g->m.ts] != '0' ||
		g->m.a[((int)tmp[1] + g->p.s / 2 - 1) / g->m.ts]
		[((int)g->p.p[0] + i - g->p.s / 2 + 1) / g->m.ts] != '0')
			g->p.coll[1] = 1;
		if (g->m.a[((int)g->p.p[1] - g->p.s / 2 + 1 + i) / g->m.ts]
		[((int)tmp[0] - g->p.s / 2 + 1) / g->m.ts] != '0' ||
		g->m.a[((int)g->p.p[1] - g->p.s / 2 + 1) / g->m.ts]
		[((int)tmp[0] - g->p.s / 2 + 1 + i) / g->m.ts] != '0' ||
		g->m.a[((int)g->p.p[1] - g->p.s / 2 + 1 + i) / g->m.ts]
		[((int)tmp[0] + g->p.s / 2 - 1) / g->m.ts] != '0' ||
		g->m.a[((int)g->p.p[1] + g->p.s / 2 - 1) / g->m.ts]
		[((int)tmp[0] - g->p.s / 2 + 1 + i) / g->m.ts] != '0')
			g->p.coll[0] = 1;
	}
}

int			hi(t_g *g)
{
	static double	tmp[2];

	g->p.coll[0] = 0;
	g->p.coll[1] = 0;
	g->p.o += (g->p.t[1] - g->p.t[0]) * g->dtr * g->p.rs;
	tmp[0] = g->p.p[0] + ((g->p.w[1] - g->p.w[0]) * g->p.ms * sin(g->p.o))
	- ((g->p.w[3] - g->p.w[2]) * g->p.ms * cos(g->p.o));
	tmp[1] = g->p.p[1] + ((g->p.w[1] - g->p.w[0]) * g->p.ms * cos(g->p.o))
	+ ((g->p.w[3] - g->p.w[2]) * g->p.ms * sin(g->p.o));
	collditions(g, tmp);
	g->p.p[0] = !g->p.coll[0] ? tmp[0] : g->p.p[0];
	g->p.p[1] = !g->p.coll[1] ? tmp[1] : g->p.p[1];
	dothestuff(g->p, g);
	mlx_put_image_to_window(g->tb.p, g->tb.w, g->tb.bi, 0, 0);
	return (0);
}
