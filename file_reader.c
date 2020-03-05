/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 23:39:51 by arhallab          #+#    #+#             */
/*   Updated: 2020/03/05 01:37:50 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static char	gfnsc(char *l)
{
	while (*l == ' ')
		l++;
	return (*l);
}

static void	distributitwo(t_g *g, char **t)
{
	(g->tt = ft_split(t[1], ',')) && ++g->whotofree[2] ? 0 : exit(ps(MF, g));
	if (!ft_strcmp(t[0], "F"))
	{
		stlen(t) != 2 || ocins("0123456789, ", t[1]) || count(t[1], ',') != 2
		|| stlen(g->tt) != 3 ||
		!isnum(g->tt[0]) || b(ft_atoi(g->tt[0])) || !isnum(g->tt[1]) ||
		b(ft_atoi(g->tt[1])) || !isnum(g->tt[2]) || b(ft_atoi(g->tt[2])) ||
		(g->checklist[6])++ ? exit(ps(ECF, g)) : 0;
		(*g).m.fc = ft_atoi(g->tt[0]) * (size_t)pow(16, 4)
		+ ft_atoi(g->tt[1]) * (size_t)pow(16, 2) + ft_atoi(g->tt[2]);
	}
	else if (!ft_strcmp(t[0], "C"))
	{
		stlen(t) != 2 || ocins("0123456789, ", t[1]) || count(t[1], ',') != 2
		|| stlen(g->tt) != 3 || !isnum(g->tt[0])
		|| b(ft_atoi(g->tt[0])) || !isnum(g->tt[1]) || b(ft_atoi(g->tt[1])) ||
		!isnum(g->tt[2]) || b(ft_atoi(g->tt[2])) || (g->checklist[7])++ ?
		exit(ps(ECF, g)) : 0;
		(*g).m.cc = ft_atoi(g->tt[0]) * (size_t)pow(16, 4)
		+ ft_atoi(g->tt[1]) * (size_t)pow(16, 2) + ft_atoi(g->tt[2]);
	}
	else
		exit(ps(EC, g));
	freetab(&(g->tt)) && g->whotofree[2]--;
}

static int	distributione(t_g *g, char **t)
{
	!t ? exit(ps(MF, g)) : 0;
	if (!ft_strcmp(t[0], "R"))
		stlen(t) != 3 || ocins("0123456789", t[1]) || ocins("0123456789", t[2])
		|| (g->res[0] = min(ft_atoi(t[1]), 2560)) <= 0 || (g->res[1] += min(
		ft_atoi(t[2]), 1440)) <= 0 || (g->checklist[0])++ ? exit(ps(ER, g)) : 0;
	else if (!ft_strcmp(t[0], "NO"))
		stlen(t) != 2 || (g->checklist[1])++ || !(g->m.nt = XFTI(g->tb.p, t[1],
		&(g->a), &(g->a))) ? exit(ps(ET, g)) : 0;
	else if (!ft_strcmp(t[0], "EA"))
		stlen(t) != 2 || (g->checklist[2])++ || !(g->m.eat = XFTI(g->tb.p, t[1],
		&(g->a), &(g->a))) ? exit(ps(ET, g)) : 0;
	else if (!ft_strcmp(t[0], "SO"))
		stlen(t) != 2 || (g->checklist[3])++ || !(g->m.sot = XFTI(g->tb.p, t[1],
		&(g->a), &(g->a))) ? exit(ps(ET, g)) : 0;
	else if (!ft_strcmp(t[0], "WE"))
		stlen(t) != 2 || (g->checklist[4])++ || !(g->m.wet = XFTI(g->tb.p, t[1],
		&(g->a), &(g->a))) ? exit(ps(ET, g)) : 0;
	else if (!ft_strcmp(t[0], "S"))
		stlen(t) != 2 || (g->checklist[5])++ || !(g->m.st = XFTI(g->tb.p, t[1],
		&(g->a), &(g->a))) ? exit(ps(ET, g)) : 0;
	else
		distributitwo(g, t);
	return (1);
}

static int	mapcheck(t_g *g, size_t i, int f)
{
	char		*nl;
	int			j;

	(void)f;
	// if (g->l[0] != '1')
	// {
	// 	g->l[0] ? exit(ps(EC, g)) : 0;
	// 	g->m.row && ocins("1 ", g->m.a[g->m.row - 1]) ? exit(ps(EM, g)) : 0;
	// 	g->m.row ? (g->m.mend = 1) : 0;
	// 	if (!f)
	// 		return (1);
	// 	return (2);
	// }
	(nl = ft_strdup(g->l)) ? 0 : exit(ps(MF, g));
	ft_realloc((void *)&(g->m.a), (g->m.row + 2), sizeof(char *))
	? 0 : exit(ps(MF, g));
	g->m.col >= ft_strlen(nl) ? 0 : (g->m.col = ft_strlen(nl));
	(((!f || !g->m.row) && ocins("1", nl)) ||
	ocins("120NEWS ", nl) ? exit(ps(EM, g)) : 0);
	while (++i < ft_strlen(nl))
		if (chrinstr("NESW", nl[i]))
			g->pe++ ? exit(ps(EM, g)) : (g->p = new_plr(i, g->m,
			!(nl[i] - 'W') + !(nl[i] - 'S') * 2 + !(nl[i] - 'E') * 3
			+ (nl[i] = '0')));
	i -= i + 1;
	g->m.a[g->m.row++] = nl;
	g->m.a[g->m.row] = 0;
	while (++i < g->m.row && (j = -1))
	{
		
	}
	return (0);
}

void		readdotcub(t_g *g, int fd)
{
	static int	f = 1;
	size_t		i;
	static int	c = 0;

	while (((i = -1) || 1))
	{
		(f *= get_next_line(fd, &g->l)) == -1 ? exit(ps(MF, g)) : 0;
		g->whotofree[0] = 1;
		g->m.mend && g->l[0] ? exit(ps(EC, g)) : 0;
		if (chrinstr("RNESWFC", gfnsc(&(g->l[0]))) && c++ < 8)
			distributione(g, g->t = split_1space(g->l)) && freetab(&(g->t))
			&& (g->whotofree[1] = 0);
		else if (c == 8)
		{
			mapcheck(g, i, f);
		}
		else if (gfnsc(&(g->l[0])))
			exit(ps("EC", g));
		free(g->l);
		if (!(g->whotofree[0] = 0) && (!f || i == 1))
			break ;
	}
	!g->pe || c != 8 ? exit((!g->pe && ps(EM, g)) || (c != 8 && ps(EC, g))) : 0;
}
