/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:50:34 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/07 11:12:02 by arhallab         ###   ########.fr       */
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

void	ppii(t_g *g, size_t x, size_t y, size_t c)
{
	if (x < g->m.ts * g->m.col && y < g->m.ts * g->m.row)
		g->tb.i_a[x + y * g->m.ts * g->m.col] = c;
}

void	ppii2(t_g *g, int x, int y, size_t c)
{
	if (x < g->res[0] && y < g->res[1])
		g->tb.bi_a[x + y * g->res[0]] = c;
}

int		drawtile(t_g *g, int *o, int w, int h)
{
	int		i;

	i = w;
	while (h-- > 0 && (w = i))
		while (w-- > 0)
		{
			ppii(g, o[0] + h, o[1] + w, 0xFFFFFF);
		}
	return (1);
}

t_m		new_m(void)
{
	t_m		m;

	m.a = malloc(sizeof(char *));
	*m.a = 0;
	m.offset[0] = 0;
	m.offset[1] = 0;
	m.ts = 64;
	m.row = 0;
	m.col = 0;
	return (m);
}

t_pl	new_plr(size_t x, t_m m, int a)
{
	t_pl	plr;

	plr.s = m.ts / 2;
	plr.p[0] = x * m.ts + m.ts / 2;
	plr.p[1] = m.row * m.ts + m.ts / 2;
	plr.ms = m.ts / 8;
	plr.rs = 2;
	plr.w[0] = 0;
	plr.w[1] = 0;
	plr.w[2] = 0;
	plr.w[3] = 0;
	plr.t[0] = 0;
	plr.t[1] = 0;
	plr.t[2] = 0;
	plr.t[3] = 0;
	plr.o = a * M_PI_2;
	plr.ll = 0;
	plr.lu = 0;
	plr.lr = 0;
	plr.ld = 0;
	return (plr);
}

int		ft_array_realloc(char ***p, size_t size)
{
	char				**ptr;
	unsigned long long	i;

	i = 0;
	if (!(ptr = malloc(sizeof(char *) * size)))
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

void	drawplayer(t_pl p, t_g g)
{
	int		i;
	int		j;
	double	ray;
	int h = g.m.row * g.m.ts;
	int w = g.m.col * g.m.ts;

	i = -1;
	// while (++i < p.s && (j = -1))
	// 	while (++j < p.s)
	// 	{
	// 		ppii(&g, p.p[0] + i, (int)p.p[1] + j, 0xFF0000);
	// 	}
	ray = g.pl.o + g.pi_6;
	j = -1;
	while (++j < g.res[0] && ((g.n_sp = 0) || 1))
	{
		g.sct[0] = sin(ray);
		g.sct[1] = cos(ray);
		// ray -= ((ray - M_PI_2 < 0.0000001 && ray - M_PI_2 > -0.0000001)
		// || (ray + M_PI_2 < 0.0000001 && ray + M_PI_2 > -0.0000001) ? 0.0000001 : 0);
		g.sct[2] = tan(ray);
		p.ll = !!(g.sct[0] >= 0);
		p.lr = !p.ll;
		p.lu = !!(g.sct[1] >= 0);
		p.ld = !p.lu;
		// while (++i < 250)
		// 	ppii(&g, (int)(p.p[0] - sct[0] * i + p.s / 2),
		// 	(int)(p.p[1] - g.sct[1] * i + p.s / 2), 0xFF0000);
		g.tmp[0] = p.p[0] + p.s / 2;
		g.tmp[1] = p.p[1] + p.s / 2;
		g.tmp[2] = p.p[0] + p.s / 2;
		g.tmp[3] = p.p[1] + p.s / 2;

		g.tmp[1] = floor(g.tmp[1] / g.m.ts) * g.m.ts + p.ld * g.m.ts;
		g.tmp[0] = g.tmp[0] + (g.tmp[1] - (p.p[1] + p.s / 2)) * g.sct[2];
		g.tmp[2] = floor(g.tmp[2] / g.m.ts) * g.m.ts + p.lr * g.m.ts;
		g.tmp[3] = g.tmp[3] + (g.tmp[2] - (p.p[0] + p.s / 2)) / g.sct[2];

		double xh =  0, yh = -p.lu, xv = -p.ll, yv = 0;
		while ((g.tmp[2] + xv) < w && (g.tmp[3] + yv) < h
		&& (g.tmp[2] + xv) > -1 && (g.tmp[3] + yv) > -1
		&& !(g.m.a[(int)(g.tmp[3] + yv) / g.m.ts][(int)(g.tmp[2] + xv) / g.m.ts] == '1'))
		{
			if (g.m.a[(int)((g.tmp[3] + yv) / g.m.ts)][(int)((g.tmp[2] + xv) / g.m.ts)] == '2')
			{
				int b = -1;
				while(++b < g.n_sp)
					if (g.sd[b].p[0] == (int)((g.tmp[3] + xv) / g.m.ts) && g.sd[b].p[1] == (int)((g.tmp[2] + yv) / g.m.ts))
					{
						if (g.sd[b].dst > sqrt(pow((int)(g.tmp[2] + xv) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[0], 2)
							+ pow((int)(g.tmp[3] + yv) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[1], 2)) * cos(ray - g.pl.o))
						{
							g.sd[b].dst = sqrt(pow((int)(g.tmp[2] + xv) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[0], 2)
							+ pow((int)(g.tmp[3] + yv) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[1], 2)) * cos(ray - g.pl.o);
							g.sd[b].spriteh = g.dpp * g.m.ts / g.sd[b].dst;
						}
						break;
					}
				if (b == g.n_sp)
				{
					g.n_sp++;
					t_s_array_realloc(&(g.sd), g.n_sp);
					g.sd[g.n_sp - 1].p[0] = (int)((g.tmp[2] + xv) / g.m.ts);
					g.sd[g.n_sp - 1].p[1] = (int)((g.tmp[3] + yv) / g.m.ts);
					g.sd[g.n_sp - 1].dst = sqrt(pow((int)(g.tmp[2] + xv) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[0], 2)
					+ pow((int)(g.tmp[3] + yv) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[1], 2)) * cos(ray - g.pl.o);
					g.sd[g.n_sp - 1].spriteh = g.dpp * g.m.ts / g.sd[g.n_sp - 1].dst;
				}
			}
			yv += (g.m.ts / g.sct[2]) * (g.sct[0] < 0 ? 1 : -1);
			xv += g.m.ts * (g.sct[0] < 0 ? 1 : -1);
		}
		while ((g.tmp[0] + xh) < w && (g.tmp[1] + yh) < h
		&& (g.tmp[0] + xh) > -1 && (g.tmp[1] + yh) > -1
		&& !(g.m.a[(int)((g.tmp[1] + yh) / g.m.ts)][(int)((g.tmp[0] + xh) / g.m.ts)] == '1'))
		{
			if (g.m.a[(int)((g.tmp[1] + yh) / g.m.ts)][(int)((g.tmp[0] + xh) / g.m.ts)] == '2')
			{
				int b = -1;
				while(++b < g.n_sp)
					if (g.sd[b].p[0] == (int)((g.tmp[0] + xh) / g.m.ts) && g.sd[b].p[1] == (int)((g.tmp[1] + yh) / g.m.ts))
					{
						if (g.sd[b].dst > sqrt(pow((int)(g.tmp[0] + xh) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[0], 2)
						+ pow((int)(g.tmp[1] + yh) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[1], 2)) * cos(ray - g.pl.o))
						{
							g.sd[b].dst = sqrt(pow((int)(g.tmp[0] + xh) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[0], 2)
							+ pow((int)(g.tmp[1] + yh) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[1], 2)) * cos(ray - g.pl.o);
							g.sd[b].spriteh = g.dpp * g.m.ts / g.sd[b].dst;
						}
						break;
					}
				if (b == g.n_sp)
				{
					g.n_sp++;
					t_s_array_realloc(&(g.sd), g.n_sp);
					g.sd[g.n_sp - 1].p[0] = (int)((g.tmp[0] + xh) / g.m.ts);
					g.sd[g.n_sp - 1].p[1] = (int)((g.tmp[1] + yh) / g.m.ts);
					g.sd[g.n_sp - 1].dst = sqrt(pow((int)(g.tmp[0] + xh) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[0], 2)
					+ pow((int)(g.tmp[1] + yh) / (g.m.ts / 2) * (g.m.ts / 2) - g.pl.p[1], 2)) * cos(ray - g.pl.o);
					g.sd[g.n_sp - 1].spriteh = g.dpp * g.m.ts / g.sd[g.n_sp - 1].dst;
				}
			}
			xh += g.m.ts * g.sct[2] * (g.sct[1] < 0 ? 1 : -1);
			yh += g.m.ts * (g.sct[1] < 0 ? 1 : -1);
		}
		g.tmp[0] += xh - p.s / 2;
		g.tmp[1] += yh - p.s / 2 + p.lu;
		g.tmp[2] += xv - p.s / 2 + p.ll;
		g.tmp[3] += yv - p.s / 2;

		if (sqrt(pow(g.tmp[0] - g.pl.p[0], 2) + pow(g.tmp[1] - g.pl.p[1], 2)) >=
		sqrt(pow(g.tmp[2] - g.pl.p[0], 2) + pow(g.tmp[3] - g.pl.p[1], 2)))
		{
			g.tmp[0] = g.tmp[2];
			g.tmp[1] = g.tmp[3];
		}
		
		sprite_rsort(&(g.sd), g.n_sp);
		
		i = -1;
		double	raydistance = 0;
		raydistance = sqrt(pow(g.tmp[0] - g.pl.p[0], 2)
		+ pow(g.tmp[1] - g.pl.p[1], 2));
		raydistance = raydistance * cos(g.pl.o - ray);
		int		wallh = g.dpp * g.m.ts / raydistance;
		// double gr = raydistance / (g.m.ts * 8) + 1;
		while (++i < g.res[1])
		{
			if (i < (g.res[1] - wallh) / 2)
				ppii2(&g, j, i, g.m.cc);
			else if (i > g.res[1] / 2 + wallh / 2)
				ppii2(&g, j, i, g.m.fc);
			else
			{
				if (g.tmp[0] != g.tmp[2])
				{
					if (g.sct[1] > 0)
						ppii2(&g, j, i, g.m.na[((int)g.tmp[0] + p.s / 2) % 64 + ((i - (g.res[1] - wallh) / 2) * 63 / wallh) * 64] + 100);
					else
						ppii2(&g, j, i, g.m.na[63 - ((int)g.tmp[0] + p.s / 2) % 64 + ((i - (g.res[1] - wallh) / 2) * 63 / wallh) * 64]);
				}
				else
				{
					if (g.sct[0] > 0)
						ppii2(&g, j, i, g.m.na[63 - ((int)g.tmp[1] + p.s / 2) % 64 + ((i - (g.res[1] - wallh) / 2) * 63 / wallh) * 64] + 300);
					else
						ppii2(&g, j, i, g.m.na[((int)g.tmp[1] + p.s / 2) % 64 + ((i - (g.res[1] - wallh) / 2) * 63 / wallh) * 64] + 200);
				}
			}
			int k = -1;
			while(++k < g.n_sp)
			{
				if (i < (g.res[1] - g.sd[k].spriteh) / 2 || i > (g.res[1] / 2) + (g.sd[k].spriteh / 2) || g.sd[k].dst > raydistance)
				{
					continue;
				}
				else
				{
					ppii2(&g, j, i, g.m.na[((int)g.tmp[1] + p.s / 2) % 64 + ((i - (g.res[1] - g.sd[k].spriteh) / 2) * 63 / g.sd[k].spriteh) * 64]);
				}
			}
		}
		ray -= g.sfr;
	}
}

void	drawmap(t_m m, t_g *g)
{
	int		o[2];
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < m.row)
	{
		j = -1;
		while (++j < ft_strlen(m.a[i]))
		{
			if (m.a[i][j] != ' ')
			{
				o[1] = i * m.ts;
				o[0] = j * m.ts;
				drawtile(g, o, m.ts * (m.a[i][j] -
				48), m.ts * (m.a[i][j] - 48));
			}
		}
	}
}

int	kp(int k, t_pl *p)
{
	if (k == 13)
		p->w[0] = 1;
	if (k == 1)
		p->w[1] = 1;
	if (k == 2)
		p->w[2] = 1;
	if (!k)
		p->w[3] = 1;
	if (k == 124)
		p->t[0] = 1;
	if (k == 123)
		p->t[1] = 1;
	return (1);
}

int	kr(int k, t_pl *p)
{
	if (k == 13)
		p->w[0] = 0;
	if (k == 1)
		p->w[1] = 0;
	if (k == 2)
		p->w[2] = 0;
	if (!k)
		p->w[3] = 0;
	if (k == 124)
		p->t[0] = 0;
	if (k == 123)
		p->t[1] = 0;
	return (1);
}

int	hi(t_g *g)
{
	double	tmp[2];
	int		i;

	// g->tb.i = mlx_new_image(g->tb.p, g->m.ts * g->m.col, g->m.ts * g->m.row);
	// g->tb.i_a = (int *)mlx_get_data_addr(g->tb.i, &g->yuzless, &g->yuzless, &g->yuzless);
	g->tb.bi = mlx_new_image(g->tb.p, g->res[0], g->res[1]);
	g->tb.bi_a = (int *)mlx_get_data_addr(g->tb.bi, &g->yuzless, &g->yuzless, &g->yuzless);
	i = -1;
	g->pl.coll[0] = 0;
	g->pl.coll[1] = 0;
	// drawmap(g->m, g);
	g->pl.o += (g->pl.t[1] - g->pl.t[0]) * M_PI * g->pl.rs / 180;
	tmp[0] = g->pl.p[0] + ((g->pl.w[1] - g->pl.w[0]) * g->pl.ms * sin(g->pl.o));
	tmp[1] = g->pl.p[1] + ((g->pl.w[1] - g->pl.w[0]) * g->pl.ms * cos(g->pl.o));
	while (++i < g->pl.s)
	{
		if (g->m.a[((int)tmp[1] + i) / g->m.ts][(int)g->pl.p[0] / g->m.ts] == '1' ||
		g->m.a[(int)tmp[1] / g->m.ts][((int)g->pl.p[0] + i) / g->m.ts] == '1' ||
		g->m.a[((int)tmp[1] + i) / g->m.ts][((int)g->pl.p[0] + g->pl.s - 1) / g->m.ts] == '1' ||
		g->m.a[((int)tmp[1] + g->pl.s - 1) / g->m.ts][((int)g->pl.p[0] + i) / g->m.ts] == '1')
			g->pl.coll[1] = 1;
		if (g->m.a[((int)g->pl.p[1] + i) / g->m.ts][(int)tmp[0] / g->m.ts] == '1' ||
		g->m.a[(int)g->pl.p[1] / g->m.ts][((int)tmp[0] + i) / g->m.ts] == '1' ||
		g->m.a[((int)g->pl.p[1] + i) / g->m.ts][((int)tmp[0] + g->pl.s - 1) / g->m.ts] == '1' ||
		g->m.a[((int)g->pl.p[1] + g->pl.s - 1) / g->m.ts][((int)tmp[0] + i) / g->m.ts] == '1')
			g->pl.coll[0] = 1;
	}
	if (!g->pl.coll[0])
		g->pl.p[0] = tmp[0];
	if (!g->pl.coll[1])
		g->pl.p[1] = tmp[1];
	drawplayer(g->pl, *g);
	mlx_put_image_to_window(g->tb.p, g->tb.w, g->tb.bi, 0, 0);
	// mlx_put_image_to_window(g->tb.p, g->tb.w, g->tb.i, 0, 0);
	mlx_destroy_image(g->tb.p, g->tb.bi);
	// mlx_destroy_image(g->tb.p, g->tb.i);
	return (0);
}

t_g	new_game(void)
{
	t_g	g;

	g.m = new_m();
	g.tb.p = mlx_init();
	g.res[0] = 0;
	g.res[1] = 0;
	g.m.fc = 0;
	g.m.cc = 0;
	g.pe = 0;
	g.a = 32;
	g.n_sp = 0;
	return (g);
}

int			stlen(char **t)
{
	int i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

void		distribution(t_g *g, char **t)
{
	char	**tt;

	if (!ft_strcmp(t[0], "R"))
	{
		stlen(t) != 3 || ocins("0123456789", t[1]) || ocins("0123456789", t[2]) || ((*g).res[0] = ft_atoi(t[1])) <= 0 || ((*g).res[1] +=
		ft_atoi(t[2])) <= 0 ? exit(printf(ER)) : 0;
	}
	else if (!ft_strcmp(t[0], "NO"))
	{
		stlen(t) != 2 || !((*g).m.nt = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "EA"))
	{
		stlen(t) != 2 || !((*g).m.eat = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "SO"))
	{
		stlen(t) != 2 || !((*g).m.sot = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "WE"))
	{
		stlen(t) != 2 || !((*g).m.wet = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "S"))
	{
		stlen(t) != 2 || !((*g).m.st = mlx_xpm_file_to_image((*g).tb.p, t[1], &((*g).a), &((*g).a))) ? exit(printf(ET)) : 0;
	}
	else if (!ft_strcmp(t[0], "F"))
	{
		stlen(t) != 2 || ocins("0123456789,", t[1]) || stlen(tt = ft_split(t[1], ',')) != 3 || ft_atoi(tt[0]) < 0 || ft_atoi(tt[1]) < 0 || ft_atoi(tt[2]) < 0
		? exit(printf(ECF)) : 0;
		(*g).m.fc = ft_atoi(tt[0]) * (size_t)pow(16, 4) + ft_atoi(tt[1]) * (size_t)pow(16, 2) + ft_atoi(tt[2]);
	}
	else if (!ft_strcmp(t[0], "C"))
	{
		stlen(t) != 2 || ocins("0123456789,", t[1]) || stlen(tt = ft_split(t[1], ',')) != 3 || ft_atoi(tt[0]) < 0 || ft_atoi(tt[1]) < 0 || ft_atoi(tt[2]) < 0
		? exit(printf(ECF)) : 0;
		(*g).m.cc = ft_atoi(tt[0]) * (size_t)pow(16, 4) + ft_atoi(tt[1]) * (size_t)pow(16, 2) + ft_atoi(tt[2]);
	}
	else
	{
		exit(printf(EC));
	}
}

char		*strdup_spe(char *s, char c)
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
		if (!(l[0]))
			continue;
		t = ft_split(l, ' ');
		if (chrinstr("RNESWFC", l[0]) && (c++ || 1))
			distribution(g, t);
		else if (c == 8)
		{
			ft_array_realloc(&(*g).m.a, (*g).m.row + 2);
			((!f || !(*g).m.row) && ocins("1 ", l)) || l[ft_strlen(l) - 1] != '1'
			|| l[0] != '1' || ocins("120NEWS ", l) || (g->m.col && g->m.col != ft_strlen(strdup_spe(l, ' ')))? exit(printf(EM)) : 0;
			g->m.col ? 0 : (g->m.col = ft_strlen(strdup_spe(l, ' ')));
			while (++i < ft_strlen(l))
			{
				if (chrinstr("NESW", l[i]))
				{
					if ((*g).pe)
						exit(printf(EM));
					(*g).pl = new_plr(i / 2, (*g).m, !(l[i] - 69) +
					!(l[i] - 83) * 2 + !(l[i] - 87) * 3);
					l[i] = '0';
					(*g).pe++;
				}
			}
			(*g).m.a[(*g).m.row++] = strdup_spe(l, ' ');
			(*g).m.a[(*g).m.row] = 0;
		}
		if (!f)
			break ;
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
	g.dpp = (g.res[0] / 2) / tan((60 * M_PI / 180) / 2);
	g.sfr = (M_PI / 3) / g.res[0];
	g.pi_6 = M_PI / 6;
	g.tb.w = mlx_new_window(g.tb.p, g.res[0], g.res[1], "lul");
	close(fd);
	mlx_hook(g.tb.w, 2, 0L, kp, &g.pl);
	mlx_hook(g.tb.w, 3, 0L, kr, &g.pl);
	mlx_loop_hook(g.tb.p, hi, &g);
	mlx_loop(g.tb.p);
	return (0);
}