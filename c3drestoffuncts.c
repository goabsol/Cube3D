/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3drestoffuncts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 08:43:27 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/28 23:33:26 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static void	spritedetect(t_g *g, int v, t_pl p)
{
	t_s *t;

	t_s_array_realloc(&(g->sd), g->n_sp + 1) ? 0 : exit(ps(MF, g));
	t = &(g->sd[g->n_sp]);
	t->c[0] = (int)g->tmp[0 + 2 * v] / g->m.ts * g->m.ts + g->m.ts / 2;
	t->c[1] = (int)g->tmp[1 + 2 * v] / g->m.ts * g->m.ts + g->m.ts / 2;
	t->dst = dst(t->c[0], p.p[0], t->c[1], p.p[1]);
	t->p[0] = p.p[0] - g->sct[0] * t->dst;
	t->p[1] = p.p[1] - g->sct[1] * t->dst;
	t->sh = g->dpp * g->m.ts / t->dst;
	t->dfc = dst(t->c[0], t->p[0], t->c[1], t->p[1]);
	t->stop = (g->res[1] / 2) - (t->sh / 2);
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

void		raycast(t_g *g, int h, int w, t_pl p)
{
	while (g->tmp[0] < w && g->tmp[1] < h && g->tmp[0] > -1 && g->tmp[1] > -1
	&& g->m.a[(int)g->tmp[1] / g->m.ts][(int)g->tmp[0] / g->m.ts] != '1')
	{
		if (g->m.a[(int)g->tmp[1] / g->m.ts][(int)g->tmp[0] / g->m.ts] == '2')
			spritedetect(g, 0, p);
		g->tmp[0] += g->step[0];
		g->tmp[1] += g->step[1];
	}
	while (g->tmp[2] < w && g->tmp[3] < h && g->tmp[2] >= 0 && g->tmp[3] >= 0
	&& g->m.a[(int)g->tmp[3] / g->m.ts][(int)g->tmp[2] / g->m.ts] != '1')
	{
		if (g->m.a[(int)g->tmp[3] / g->m.ts][(int)g->tmp[2] / g->m.ts] == '2')
			spritedetect(g, 1, p);
		g->tmp[3] += g->step[2];
		g->tmp[2] += g->step[3];
	}
	g->tmp[1] += p.lu;
	g->tmp[2] += p.ll;
	g->yzle = 0;
}

void		startingpoint(t_g *g, t_pl *p, double ray)
{
	g->sct[0] = sin(ray);
	g->sct[1] = cos(ray);
	g->sct[2] = tan(ray);
	p->ll = !!(g->sct[0] >= 0);
	p->lr = !p->ll;
	p->lu = !!(g->sct[1] >= 0);
	p->ld = !p->lu;
	g->tmp[1] = floor(p->p[1] / g->m.ts) * g->m.ts + p->ld * g->m.ts - p->lu;
	g->tmp[0] = p->p[0] + (g->tmp[1] + p->lu - p->p[1]) * g->sct[2];
	g->tmp[2] = floor(p->p[0] / g->m.ts) * g->m.ts + p->lr * g->m.ts - p->ll;
	g->tmp[3] = p->p[1] + (g->tmp[2] + p->ll - p->p[0]) / g->sct[2];
	g->step[0] = g->m.ts * g->sct[2] * (g->sct[1] < 0 ? 1 : -1);
	g->step[1] = g->m.ts * (g->sct[1] < 0 ? 1 : -1);
	g->step[2] = (g->m.ts / g->sct[2]) * (g->sct[0] < 0 ? 1 : -1);
	g->step[3] = g->m.ts * (g->sct[0] < 0 ? 1 : -1);
}
