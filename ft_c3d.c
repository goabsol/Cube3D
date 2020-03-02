/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:50:34 by arhallab          #+#    #+#             */
/*   Updated: 2020/03/02 15:53:27 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static t_rc	new_rc(t_g *g, double raydistance)
{
	t_rc	n;

	n.wallh = g->dpp * g->m.ts / raydistance;
	n.wbot = g->res[1] / 2 + n.wallh / 2;
	n.wtop = (g->res[1] - n.wallh) / 2;
	n.x1 = (int)g->tmp[0] % 64;
	n.x2 = 63 - n.x1;
	n.x3 = (int)g->tmp[1] % 64;
	n.x4 = 63 - n.x3;
	n.c1 = (g->res[1] - n.wallh) / 2;
	n.c2 = 63.0 / n.wallh;
	return (n);
}

static void	renderingsprite(t_g *g, double raydistance, t_rc *c, int i)
{
	t_s			t;
	int			k;

	k = -1;
	while (++k < g->n_sp)
	{
		t = g->sd[k];
		if (i >= t.stop && i <= t.sbot &&
		t.dfc <= 32 && t.dst <= raydistance)
		{
			if (!t.co1 && g->m.sa[t.x1 +
			(int)((i - t.c1) * t.c2) * 64] != 0XFF33FF)
				g->tb.bi_a[c->c] = g->m.sa[t.x1
				+ (int)((i - t.c1) * t.c2) * 64];
			else if (t.co1 && g->m.sa[t.x2 +
			(int)((i - t.c1) * t.c2) * 64] != 0XFF33FF)
				g->tb.bi_a[c->c] = g->m.sa[t.x2
				+ (int)((i - t.c1) * t.c2) * 64];
		}
	}
}

static void	renderingwall(t_g *g, int j, double raydistance, t_pl p)
{
	int			i;
	t_rc		c;

	i = -1;
	c = new_rc(g, raydistance);
	while (++i < g->res[1])
	{
		c.c = j + i * g->res[0];
		if (i < c.wtop)
			g->tb.bi_a[c.c] = g->m.cc;
		else if (i > c.wbot)
			g->tb.bi_a[c.c] = g->m.fc;
		else if (!g->yzle && p.lu)
			g->tb.bi_a[c.c] = g->m.soa[c.x1 + (int)((i - c.c1) * c.c2) * 64];
		else if (!g->yzle && p.ld)
			g->tb.bi_a[c.c] = g->m.na[c.x2 + (int)((i - c.c1) * c.c2) * 64];
		else if (g->yzle && p.lr)
			g->tb.bi_a[c.c] = g->m.wea[c.x3 + (int)((i - c.c1) * c.c2) * 64];
		else if (g->yzle && p.ll)
			g->tb.bi_a[c.c] = g->m.eaa[c.x4 + (int)((i - c.c1) * c.c2) * 64];
		renderingsprite(g, raydistance, &c, i);
	}
	free(g->sd);
	g->sd = NULL;
}

void		dothestuff(t_pl p, t_g *g)
{
	int			j;
	static int	f = 1;
	double		ray;

	ray = g->p.o + g->pi_6;
	j = -1;
	while (++j < g->res[0] && ((g->n_sp = 0) || 1))
	{
		startingpoint(g, &p, ray);
		raycast(g, g->m.row * g->m.ts, g->m.col * g->m.ts, p);
		if (sqrt(pow(g->tmp[0] - p.p[0], 2) + pow(g->tmp[1] - p.p[1], 2)) >=
		sqrt(pow(g->tmp[2] - p.p[0], 2) + pow(g->tmp[3] - p.p[1], 2)))
			((g->tmp[0] += g->tmp[2] - g->tmp[0]) || 1) && (g->yzle = 1)
			&& (g->tmp[1] = g->tmp[3]);
		sprite_rsort(&(g->sd), g->n_sp);
		renderingwall(g, j, sqrt(pow(g->tmp[0] - g->p.p[0], 2)
		+ pow(g->tmp[1] - g->p.p[1], 2)) * cos(g->p.o - ray), p);
		ray -= g->sfr;
	}
	if (g->save)
	{
		screen(g);
		f = 0;
		exit(ps(NULL, g));
	}
}

int			main(int a, char **b)
{
	int		fd;
	t_g		g;

	g = new_game();
	check_args(a, b, &g);
	(fd = open(b[1], O_RDONLY)) == -1 ? exit(ps(NF, &g)) : 0;
	readdotcub(&g, fd);
	g.m.na = (int *)mlx_get_data_addr(g.m.nt, &g.yzle, &g.yzle, &g.yzle);
	g.m.eaa = (int *)mlx_get_data_addr(g.m.eat, &g.yzle, &g.yzle, &g.yzle);
	g.m.wea = (int *)mlx_get_data_addr(g.m.wet, &g.yzle, &g.yzle, &g.yzle);
	g.m.soa = (int *)mlx_get_data_addr(g.m.sot, &g.yzle, &g.yzle, &g.yzle);
	g.m.sa = (int *)mlx_get_data_addr(g.m.st, &g.yzle, &g.yzle, &g.yzle);
	g.dpp = (g.res[0] / 2) / tan((60 * M_PI / 180) / 2);
	g.sfr = (M_PI / 3) / g.res[0];
	!g.save && (g.tb.w = mlx_new_window(g.tb.p, g.res[0], g.res[1], C))
	&& (g.tb.aw++);
	(g.tb.bi = mlx_new_image(g.tb.p, g.res[0], g.res[1])) && (g.tb.animg++);
	g.tb.bi_a = (int *)mlx_get_data_addr(g.tb.bi, &g.yzle, &g.yzle, &g.yzle);
	close(fd);
	!g.save && mlx_hook(g.tb.w, 2, 0L, kp, &g);
	!g.save && mlx_hook(g.tb.w, 3, 0L, kr, &g);
	!g.save && mlx_hook(g.tb.w, 17, 0L, closewindow, &g);
	mlx_loop_hook(g.tb.p, hi, &g);
	mlx_loop(g.tb.p);
	return (0);
}
