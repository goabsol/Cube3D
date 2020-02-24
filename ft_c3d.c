/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:50:34 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/24 04:29:47 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void	spritedetect(t_g *g, int v, t_pl p)
{
	t_s *t;

	t_s_array_realloc(&(g->sd), g->n_sp + 1);
	t = &(g->sd[g->n_sp]);
	t->c[0] = (int)g->tmp[0 + 2 * v] / g->m.ts * g->m.ts + g->m.ts / 2;
	t->c[1] = (int)g->tmp[1 + 2 * v] / g->m.ts * g->m.ts + g->m.ts / 2;
	t->dst = sqrt(pow(t->c[0] - p.p[0], 2) + pow(t->c[1] - p.p[1], 2));
	t->p[0] = p.p[0] - g->sct[0] * t->dst;
	t->p[1] = p.p[1] - g->sct[1] * t->dst;
	t->sh = g->dpp * g->m.ts / t->dst;
	t->dfc = sqrt(pow(t->c[0] - t->p[0], 2) + pow(t->c[1] - t->p[1], 2));
	t->stop = g->res[1] / 2;
	t->sbot = (g->res[1] / 2) + (t->sh / 2);
	t->co1 = (t->p[0] > t->c[0] && p.lu) || (t->p[0] < t->c[0] && p.ld);
	t->co2 = (t->p[1] < p.p[1] && p.p[1] < t->c[1] && p.lr) ||
	(t->p[1] > p.p[1] - 1 && p.p[1] > t->c[1] && p.ll);
	t->co3 = (t->p[1] > p.p[1] && p.p[1] > t->c[1] && p.lr) ||
	(t->p[1] < p.p[1] + 1 && p.p[1] < t->c[1] && p.ll);
	t->co1 = (t->co1 && t->co2) || (!t->co1 && !t->co3);
	t->x1 = (int)t->dfc + g->m.ts / 2;
	t->x2 = 63 - t->x1;
	t->c1 = (g->res[1] - t->sh) / 2;
	t->c2 = 63.0 / t->sh;
	g->n_sp++;
}

void	raycast(t_g *g, int h, int w, t_pl p)
{
	while (g->tmp[0] < w && g->tmp[1] < h
	&& g->tmp[0] > -1 && g->tmp[1] > -1
	&& !(g->m.a[(int)g->tmp[1] / g->m.ts][(int)g->tmp[0] / g->m.ts] == '1'))
	{
		if (g->m.a[(int)g->tmp[1] / g->m.ts][(int)g->tmp[0] / g->m.ts] == '2')
			spritedetect(g, 0, p);
		g->tmp[0] += g->step[0];
		g->tmp[1] += g->step[1];
	}
	g->step[0] = (g->m.ts / g->sct[2]) * (g->sct[0] < 0 ? 1 : -1);
	g->step[1] = g->m.ts * (g->sct[0] < 0 ? 1 : -1);
	while (g->tmp[2] < w && g->tmp[3] < h && g->tmp[2] >= 0 && g->tmp[3] >= 0
	&& !(g->m.a[(int)g->tmp[3] / g->m.ts][(int)g->tmp[2] / g->m.ts] == '1'))
	{
		if (g->m.a[(int)g->tmp[3] / g->m.ts][(int)g->tmp[2] / g->m.ts] == '2')
			spritedetect(g, 1, p);
		g->tmp[3] += g->step[0];
		g->tmp[2] += g->step[1];
	}
	g->tmp[1] += p.lu;
	g->tmp[2] += p.ll;
	g->yuzless = 0;
}

void	rendering (t_g *g, int j, double raydistance, t_pl p)
{
	static int	k = -1;
	int			i;
	// needs a struct
	int			wallh = g->dpp * g->m.ts / raydistance;
	int 		wbot = g->res[1] / 2 + wallh / 2, wtop = (g->res[1] - wallh) / 2;
	int 		x1 = (int)g->tmp[0] % 64;
	int			x2 = 63 - x1;
	int			x3 = (int)g->tmp[1] % 64;
	int			x4 = 63 - x3;
	int 		c1 = (g->res[1] - wallh) / 2;
	double 		c2 = 63.0 / wallh;
	int			test1;

	i = -1;
	while (++i < g->res[1] && (k = -1))
	{
		test1 = j + i * g->res[0];
		if (i < wtop)
			g->tb.bi_a[test1] = g->m.cc;
		else if (i > wbot)
			g->tb.bi_a[test1] = g->m.fc;
		else
		{
			if (!g->yuzless && p.lu)
				g->tb.bi_a[test1] = g->m.na[x1 + (int)((i - c1) * c2) * 64];
			else if (!g->yuzless && p.ld)
				g->tb.bi_a[test1] = g->m.na[x2 + (int)((i - c1) * c2) * 64];
			else if (g->yuzless && p.lr)
				g->tb.bi_a[test1] = g->m.na[x3 + (int)((i - c1) * c2) * 64];
			else
				g->tb.bi_a[test1] = g->m.na[x4 + (int)((i - c1) * c2) * 64];
		}
		while(++k < g->n_sp)
			if (i >= g->sd[k].stop && i <= g->sd[k].sbot && g->sd[k].dfc <= 30 && g->sd[k].dst <= raydistance)
			{
				if(!g->sd[k].co1 && g->m.sa[g->sd[k].x1 + (int)((i - g->sd[k].c1) * g->sd[k].c2) * 64] != 0XFF33FF)
					g->tb.bi_a[test1] = g->m.sa[g->sd[k].x1 + (int)((i - g->sd[k].c1) * g->sd[k].c2) * 64];
				else if (g->sd[k].co1 && g->m.sa[g->sd[k].x2 + (int)((i - g->sd[k].c1) * g->sd[k].c2) * 64] != 0XFF33FF)
					g->tb.bi_a[test1] = g->m.sa[g->sd[k].x2 + (int)((i - g->sd[k].c1) * g->sd[k].c2) * 64];
			}		
	}
}

void	drawplayer(t_pl p, t_g g)
{
	int		j;
	double	ray;

	ray = g.p.o + g.pi_6;
	j = -1;
	while (++j < g.res[0] && ((g.n_sp = 0) || 1))
	{
		g.sct[0] = sin(ray);
		g.sct[1] = cos(ray);
		g.sct[2] = tan(ray);
		p.ll = !!(g.sct[0] >= 0);
		p.lr = !p.ll;
		p.lu = !!(g.sct[1] >= 0);
		p.ld = !p.lu;
		g.tmp[1] = floor(p.p[1] / g.m.ts) * g.m.ts + p.ld * g.m.ts;
		g.tmp[0] = p.p[0] + (g.tmp[1] - (p.p[1])) * g.sct[2];
		g.tmp[2] = floor(p.p[0] / g.m.ts) * g.m.ts + p.lr * g.m.ts;
		g.tmp[3] = p.p[1] + (g.tmp[2] - (p.p[0])) / g.sct[2];
		g.tmp[2] -= p.ll;
		g.tmp[1] -= p.lu;
		g.step[0] = g.m.ts * g.sct[2] * (g.sct[1] < 0 ? 1 : -1);
		g.step[1] = g.m.ts * (g.sct[1] < 0 ? 1 : -1);
		raycast(&g, g.m.row * g.m.ts, g.m.col * g.m.ts, p);
		if (sqrt(pow(g.tmp[0] - p.p[0], 2) + pow(g.tmp[1] - p.p[1], 2)) >=
		sqrt(pow(g.tmp[2] - p.p[0], 2) + pow(g.tmp[3] - p.p[1], 2)))
		{
			g.tmp[0] = g.tmp[2];
			g.tmp[1] = g.tmp[3];
			g.yuzless = 1;
		}
		sprite_rsort(&(g.sd), g.n_sp);
		double	raydistance = 0;
		raydistance = sqrt(pow(g.tmp[0] - g.p.p[0], 2)
		+ pow(g.tmp[1] - g.p.p[1], 2));
		raydistance = raydistance * cos(g.p.o - ray);
		rendering (&g, j, raydistance, p);
		ray -= g.sfr;
	}
}

// int		drawtile(t_g *g, int *o, int w, int h)
// {
// 	int		i;

// 	i = w;
// 	while (h-- > 0 && (w = i))
// 		while (w-- > 0)
// 		{
// 			ppii(g, o[0] + h, o[1] + w, 0xFFFFFF);
// 		}
// 	return (1);
// }

// void	drawmap(t_m m, t_g *g)
// {
// 	int		o[2];
// 	size_t	i;
// 	size_t	j;

// 	i = -1;
// 	while (++i < m.row)
// 	{
// 		j = -1;
// 		while (++j < ft_strlen(m.a[i]))
// 		{
// 			if (m.a[i][j] != ' ')
// 			{
// 				o[1] = i * m.ts;
// 				o[0] = j * m.ts;
// 				drawtile(g, o, m.ts * (m.a[i][j] -
// 				48), m.ts * (m.a[i][j] - 48));
// 			}
// 		}
// 	}
// }

int		main(int a, char **b)
{
	int		fd;
	t_g	g;

	a != 2 ? exit(ps("Error\nno || >1 file submitted")) : 0;
	g = new_game();
	fd = open(b[1], O_RDONLY);
	g.tb.p = mlx_init();
	g.m.mend = 0;
	readdotcub(&g, fd);
	g.m.na = (int *)mlx_get_data_addr(g.m.nt, &g.yuzless, &g.yuzless, &g.yuzless);
	g.m.eaa = (int *)mlx_get_data_addr(g.m.eat, &g.yuzless, &g.yuzless, &g.yuzless);
	g.m.wea = (int *)mlx_get_data_addr(g.m.wet, &g.yuzless, &g.yuzless, &g.yuzless);
	g.m.soa = (int *)mlx_get_data_addr(g.m.sot, &g.yuzless, &g.yuzless, &g.yuzless);
	g.m.sa = (int *)mlx_get_data_addr(g.m.st, &g.yuzless, &g.yuzless, &g.yuzless);
	g.dpp = (g.res[0] / 2) / tan((60 * M_PI / 180) / 2);
	g.sfr = (M_PI / 3) / g.res[0];
	g.pi_6 = M_PI / 6;
	g.dtr = M_PI / 180;
	g.tb.w = mlx_new_window(g.tb.p, g.res[0], g.res[1], "lul");
	g.tb.bi = mlx_new_image(g.tb.p, g.res[0], g.res[1]);
	g.tb.bi_a = (int *)mlx_get_data_addr(g.tb.bi, &g.yuzless, &g.yuzless, &g.yuzless);
	close(fd);
	mlx_hook(g.tb.w, 2, 0L, kp, &g.p);
	mlx_hook(g.tb.w, 3, 0L, kr, &g.p);
	mlx_loop_hook(g.tb.p, hi, &g);
	mlx_loop(g.tb.p);
	return (0);
}
