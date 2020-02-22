/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:50:34 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/22 17:00:04 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"



void	drawplayer(t_pl p, t_g g)
{
	int		i;
	int		j;
	double	ray;
	int h = g.m.row * g.m.ts;
	int w = g.m.col * g.m.ts;
	#include "time.h"
	i = -1;
	// while (++i < p.s && (j = -1))
	// 	while (++j < p.s)
	// 	{
	// 		ppii(&g, p.p[0] + i, (int)p.p[1] + j, 0xFF0000);
	// 	}
	ray = g.p.o + g.pi_6;
	j = -1;
	clock_t s = clock();
	while (++j < g.res[0] && ((g.n_sp = 0) || 1))
	{
		g.sct[0] = sin(ray);
		g.sct[1] = cos(ray);
		// ray += ((ray - M_PI_2 < 0.0001 && ray - M_PI_2 > -0.0001)
		// || (ray + M_PI_2 < 0.0001 && ray + M_PI_2 > -0.0001) ? 0.0001 : 0);
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
		
		while (g.tmp[0] < w && g.tmp[1] < h
		&& g.tmp[0] > -1 && g.tmp[1] > -1
		&& !(g.m.a[(int)g.tmp[1] / g.m.ts][(int)g.tmp[0] / g.m.ts] == '1'))
		{
			if (g.m.a[(int)g.tmp[1] / g.m.ts][(int)g.tmp[0] / g.m.ts] == '2')
			{
				t_s_array_realloc(&(g.sd), g.n_sp + 1);
				g.sd[g.n_sp].c[0] = (int)g.tmp[0] / g.m.ts * g.m.ts + g.m.ts / 2;
				g.sd[g.n_sp].c[1] = (int)g.tmp[1] / g.m.ts * g.m.ts + g.m.ts / 2;
				g.sd[g.n_sp].dst = sqrt(pow(g.sd[g.n_sp].c[0] - p.p[0], 2) + pow(g.sd[g.n_sp].c[1] - p.p[1], 2));
				g.sd[g.n_sp].p[0] = p.p[0] - g.sct[0] * g.sd[g.n_sp].dst;
				g.sd[g.n_sp].p[1] = p.p[1] - g.sct[1] * g.sd[g.n_sp].dst;
				g.sd[g.n_sp].sh = g.dpp * g.m.ts / g.sd[g.n_sp].dst;
				g.sd[g.n_sp].dfc = sqrt(pow(g.sd[g.n_sp].c[0] - g.sd[g.n_sp].p[0], 2) + pow(g.sd[g.n_sp].c[1] - g.sd[g.n_sp].p[1], 2));
				g.sd[g.n_sp].stop = g.res[1] / 2;
				g.sd[g.n_sp].sbot = (g.res[1] / 2) + (g.sd[g.n_sp].sh / 2);
				g.sd[g.n_sp].co1 = (g.sd[g.n_sp].p[0] > g.sd[g.n_sp].c[0] && p.lu) || (g.sd[g.n_sp].p[0] < g.sd[g.n_sp].c[0] && p.ld);
				g.sd[g.n_sp].co2 = (g.sd[g.n_sp].p[1] < p.p[1] && p.p[1] < g.sd[g.n_sp].c[1] && p.lr) || (g.sd[g.n_sp].p[1] > p.p[1] - 1 && p.p[1] > g.sd[g.n_sp].c[1] && p.ll);
				g.sd[g.n_sp].co3 = (g.sd[g.n_sp].p[1] > p.p[1] && p.p[1] > g.sd[g.n_sp].c[1] && p.lr) || (g.sd[g.n_sp].p[1] < p.p[1] + 1 && p.p[1] < g.sd[g.n_sp].c[1] && p.ll);
				g.sd[g.n_sp].co1 = (g.sd[g.n_sp].co1 && g.sd[g.n_sp].co2) || (!g.sd[g.n_sp].co1 && !g.sd[g.n_sp].co3);
				g.sd[g.n_sp].x1 = (int)g.sd[g.n_sp].dfc + g.m.ts / 2;
				g.sd[g.n_sp].x2 = 63 - g.sd[g.n_sp].x1;
				g.sd[g.n_sp].c1 = (g.res[1] - g.sd[g.n_sp].sh) / 2;
				g.sd[g.n_sp].c2 = 63.0 / g.sd[g.n_sp].sh;
				g.n_sp++;
			}
			g.tmp[0] += g.step[0];
			g.tmp[1] += g.step[1];
		}

		g.step[0] = (g.m.ts / g.sct[2]) * (g.sct[0] < 0 ? 1 : -1);
		g.step[1] = g.m.ts * (g.sct[0] < 0 ? 1 : -1);
		
		while (g.tmp[2] < w && g.tmp[3] < h && g.tmp[2] >= 0 && g.tmp[3] >= 0
		&& !(g.m.a[(int)g.tmp[3] / g.m.ts][(int)g.tmp[2] / g.m.ts] == '1'))
		{
			if (g.m.a[(int)g.tmp[3] / g.m.ts][(int)g.tmp[2] / g.m.ts] == '2')
			{
				t_s_array_realloc(&(g.sd), g.n_sp + 1);
				g.sd[g.n_sp].c[0] = (int)g.tmp[2] / g.m.ts * g.m.ts + g.m.ts / 2;
				g.sd[g.n_sp].c[1] = (int)g.tmp[3] / g.m.ts * g.m.ts + g.m.ts / 2;
				g.sd[g.n_sp].dst = sqrt(pow(g.sd[g.n_sp].c[0] - p.p[0], 2) + pow(g.sd[g.n_sp].c[1] - p.p[1], 2));
				g.sd[g.n_sp].p[0] = p.p[0] - g.sct[0] * g.sd[g.n_sp].dst;
				g.sd[g.n_sp].p[1] = p.p[1] - g.sct[1] * g.sd[g.n_sp].dst;
				g.sd[g.n_sp].sh = g.dpp * g.m.ts / g.sd[g.n_sp].dst;
				g.sd[g.n_sp].dfc = sqrt(pow(g.sd[g.n_sp].c[0] - g.sd[g.n_sp].p[0], 2) + pow(g.sd[g.n_sp].c[1] - g.sd[g.n_sp].p[1], 2));
				g.sd[g.n_sp].stop = g.res[1] / 2;
				g.sd[g.n_sp].sbot = (g.res[1] / 2) + (g.sd[g.n_sp].sh / 2);
				g.sd[g.n_sp].co1 = (g.sd[g.n_sp].p[0] > g.sd[g.n_sp].c[0] && p.lu) || (g.sd[g.n_sp].p[0] < g.sd[g.n_sp].c[0] && p.ld);
				g.sd[g.n_sp].co2 = (g.sd[g.n_sp].p[1] < p.p[1] && p.p[1] < g.sd[g.n_sp].c[1] && p.lr) || (g.sd[g.n_sp].p[1] > p.p[1] - 1 && p.p[1] > g.sd[g.n_sp].c[1] && p.ll);
				g.sd[g.n_sp].co3 = (g.sd[g.n_sp].p[1] > p.p[1] && p.p[1] > g.sd[g.n_sp].c[1] && p.lr) || (g.sd[g.n_sp].p[1] < p.p[1] + 1 && p.p[1] < g.sd[g.n_sp].c[1] && p.ll);
				g.sd[g.n_sp].co1 = (g.sd[g.n_sp].co1 && g.sd[g.n_sp].co2) || (!g.sd[g.n_sp].co1 && !g.sd[g.n_sp].co3);
				g.sd[g.n_sp].x1 = (int)g.sd[g.n_sp].dfc + g.m.ts / 2;
				g.sd[g.n_sp].x2 = 63 - g.sd[g.n_sp].x1;
				g.sd[g.n_sp].c1 = (g.res[1] - g.sd[g.n_sp].sh) / 2;
				g.sd[g.n_sp].c2 = 63.0 / g.sd[g.n_sp].sh;
				g.n_sp++;
			}
			g.tmp[3] += g.step[0];
			g.tmp[2] += g.step[1];
		}
		g.tmp[1] += p.lu;
		g.tmp[2] += p.ll;
		
		g.yuzless = 0;
		if (sqrt(pow(g.tmp[0] - g.p.p[0], 2) + pow(g.tmp[1] - g.p.p[1], 2)) >=
		sqrt(pow(g.tmp[2] - g.p.p[0], 2) + pow(g.tmp[3] - g.p.p[1], 2)))
		{
			g.tmp[0] = g.tmp[2];
			g.tmp[1] = g.tmp[3];
			g.yuzless = 1;
		}
		t_s *tsd = g.sd;
		sprite_rsort(&(tsd), g.n_sp);
		
		i = -1;
		double	raydistance = 0;
		raydistance = sqrt(pow(g.tmp[0] - g.p.p[0], 2)
		+ pow(g.tmp[1] - g.p.p[1], 2));
		raydistance = raydistance * cos(g.p.o - ray);
		int		wallh = g.dpp * g.m.ts / raydistance;
		// double gr = raydistance / (g.m.ts * 8) + 1;
		int wbot = g.res[1] / 2 + wallh / 2, wtop = (g.res[1] - wallh) / 2;
		int x1 = (int)g.tmp[0] % 64, x2 = 63 - x1, x3 = (int)g.tmp[1] % 64, x4 = 63 - x3;
		int c1 = (g.res[1] - wallh) / 2;
		double c2 = 63.0 / wallh;
		if (g.n_sp == 2)
			printf("wut\n");
		int k = -1;
		while (++i < g.res[1] && (k = -1))
		{
			int test1 = j + i * g.res[0];
			if (i < wtop)
				g.tb.bi_a[test1] = g.m.cc;
			else if (i > wbot)
				g.tb.bi_a[test1] = g.m.fc;
			else
			{
				if (!g.yuzless)
				{
					if (p.lu)
						g.tb.bi_a[test1] = g.m.na[x1 + (int)((i - c1) * c2) * 64];
					else
						g.tb.bi_a[test1] = g.m.na[x2 + (int)((i - c1) * c2) * 64];
				}
				else
				{
					if (p.lr)
						g.tb.bi_a[test1] = g.m.na[x3 + (int)((i - c1) * c2) * 64];
					else
						g.tb.bi_a[test1] = g.m.na[x4 + (int)((i - c1) * c2) * 64];
				}
			}
			while(++k < g.n_sp)
				if (i >= g.sd[k].stop && i <= g.sd[k].sbot && g.sd[k].dfc <= 30 && g.sd[k].dst <= raydistance)
				{
					// if ( || g.m.sa[g.sd[k].x2 + (int)((i - g.sd[k].c1) * g.sd[k].c2) * 64] == 0XFF33FF)
					// 	continue ;
					if(!g.sd[k].co1 && g.m.sa[g.sd[k].x1 + (int)((i - g.sd[k].c1) * g.sd[k].c2) * 64] != 0XFF33FF)
					// 255 51 255
						g.tb.bi_a[test1] = g.m.sa[g.sd[k].x1 + (int)((i - g.sd[k].c1) * g.sd[k].c2) * 64];
						// ppii2(&g, , , g.m.sa[g.sd[k].x1 + (int)((i - g.sd[k].c1) * g.sd[k].c2) * 64]);
					else if (g.sd[k].co1 && g.m.sa[g.sd[k].x2 + (int)((i - g.sd[k].c1) * g.sd[k].c2) * 64] != 0XFF33FF)
						g.tb.bi_a[test1] = g.m.sa[g.sd[k].x2 + (int)((i - g.sd[k].c1) * g.sd[k].c2) * 64];
				}
			
						
		}
		ray -= g.sfr;
	}
		printf("%lf\n", (clock() - s) / (double)CLOCKS_PER_SEC);
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

void		distribution(t_g *g, char **t)
{
	char	**tt;

	if (!ft_strcmp(t[0], "R"))
	{
		stlen(t) != 3 || ocins("0123456789", t[1]) || ocins("0123456789", t[2]) || ((*g).res[0] = MIN(ft_atoi(t[1]), 2560)) <= 0 || ((*g).res[1] += MIN(ft_atoi(t[2]), 1440)) <= 0 || (g->checklist[0])++ ? exit(printf(ER)) : 0;
	}
	else if (!ft_strcmp(t[0], "NO"))
	{
		stlen(t) != 2 || !((*g).m.nt = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) || (g->checklist[1])++ ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "EA"))
	{
		stlen(t) != 2 || !((*g).m.eat = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) || (g->checklist[2])++ ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "SO"))
	{
		stlen(t) != 2 || !((*g).m.sot = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) || (g->checklist[3])++ ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "WE"))
	{
		stlen(t) != 2 || !((*g).m.wet = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) || (g->checklist[4])++ ? exit(ps(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "S"))
	{
		stlen(t) != 2 || !((*g).m.st = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) || (g->checklist[5])++ ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "F"))
	{
		stlen(t) != 2 || ocins("0123456789,", t[1]) || count(t[1], ',') != 2 || stlen(tt = ft_split(t[1], ',')) != 3 || ft_atoi(tt[0]) < 0 || ft_atoi(tt[1]) < 0 || ft_atoi(tt[2]) < 0 || (g->checklist[6])++ ? exit(printf(ECF)) : 0;
		(*g).m.fc = ft_atoi(tt[0]) * (size_t)pow(16, 4) + ft_atoi(tt[1]) * (size_t)pow(16, 2) + ft_atoi(tt[2]);
	}
	else if (!ft_strcmp(t[0], "C"))
	{
		stlen(t) != 2 || ocins("0123456789,", t[1]) || count(t[1], ',') != 2 || stlen(tt = ft_split(t[1], ',')) != 3 || ft_atoi(tt[0]) < 0 || ft_atoi(tt[1]) < 0 || ft_atoi(tt[2]) < 0 || (g->checklist[7])++ ? exit(printf(ECF)) : 0;
		(*g).m.cc = ft_atoi(tt[0]) * (size_t)pow(16, 4) + ft_atoi(tt[1]) * (size_t)pow(16, 2) + ft_atoi(tt[2]);
	}
	else
	{
		exit(printf(EC));
	}
}

void		readdotcub(t_g *g, int fd)
{
	int		f;
	size_t	i;
	char	*l;
	int		c;
	char	**t;

	c = 0;
	while (1 && ((i = -1) || 1))
	{
		f = get_next_line(fd, &l);
		l = ft_strtrim(l, " ");
		t = ft_split(l, ' ');
		if (chrinstr("RNESWFC", l[0]) && c++ < 8)
			distribution(g, t);
		else if (c == 8)
		{
			if (l[0] != '1' && !(g->m.row))
				continue ;
			ft_array_realloc(&(*g).m.a, (*g).m.row + 2);
			g->m.col ? 0 : (g->m.col = ft_strlen(strdup_spe(l, ' ')));
			(((!f || !(*g).m.row) && ocins("1 ", l)) || l[ft_strlen(l) - 1] != '1'
			|| l[0] != '1' || ocins("120NEWS ", l) || (g->m.col && g->m.col != ft_strlen(strdup_spe(l, ' '))) ? exit(printf(EM)) : 0);
			while (++i < ft_strlen(l))
			{
				if (chrinstr("NESW", l[i]))
				{
					if ((*g).pe)
						exit(printf(EM));
					(*g).p = new_plr(i / 2, (*g).m, !(l[i] - 69) +
					!(l[i] - 83) * 2 + !(l[i] - 87) * 3);
					l[i] = '0';
					(*g).pe++;
				}
			}
			(*g).m.a[(*g).m.row++] = strdup_spe(l, ' ');
			(*g).m.a[(*g).m.row] = 0;
		}
		else if (l[0])
		{
			exit(ps(EC));
		}
		if (!f)
		{
			break ;
		}
	}
	!g->pe ? exit(printf(EM)) : 0;
	if (!(chrinstr("RNESWFC1", l[0])) || c != 8)
		exit(printf(EC));
}

int		main(int a, char **b)
{
	int		fd;
	t_g	g;

	(void)a;
	g = new_game();
	fd = open(b[1], O_RDONLY);
	g.tb.p = mlx_init();
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