/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_n_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:51:54 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/22 16:19:34 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static t_m		new_m(void)
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

t_pl			new_plr(size_t x, t_m m, int a)
{
	t_pl	plr;

	plr.s = m.ts / 8;
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

t_g				new_game(void)
{
	t_g	g;
	int	i;

	i = -1;
	while (++i < 8)
		g.checklist[i] = 0;
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

int				stlen(char **t)
{
	int i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

int				count(char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (*s++)
		i += ((*s) == c ? 1 : 0);
	return (i);
}
