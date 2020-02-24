/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 23:39:51 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/24 08:56:04 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static void	distributitwo(t_g *g, char **t)
{
	char	**tt;

	if (!ft_strcmp(t[0], "F"))
	{
		stlen(t) != 2 || ocins("0123456789, ", t[1]) || count(t[1], ',') != 2
		|| stlen(tt = ft_split(t[1], ',')) != 3 || !isnum(tt[0])
		|| B(ft_atoi(tt[0])) || !isnum(tt[1]) || B(ft_atoi(tt[1])) ||
		!isnum(tt[2]) || B(ft_atoi(tt[2])) || (g->checklist[6])++
		? exit(ps(ECF)) : 0;
		(*g).m.fc = ft_atoi(tt[0]) * (size_t)pow(16, 4)
		+ ft_atoi(tt[1]) * (size_t)pow(16, 2) + ft_atoi(tt[2]);
	}
	else if (!ft_strcmp(t[0], "C"))
	{
		stlen(t) != 2 || ocins("0123456789,", t[1]) || count(t[1], ',') != 2
		|| stlen(tt = ft_split(t[1], ',')) != 3 || ft_atoi(tt[0]) < 0 ||
		ft_atoi(tt[1]) < 0 || ft_atoi(tt[2]) < 0 || (g->checklist[7])++ ?
		exit(ps(ECF)) : 0;
		(*g).m.cc = ft_atoi(tt[0]) * (size_t)pow(16, 4)
		+ ft_atoi(tt[1]) * (size_t)pow(16, 2) + ft_atoi(tt[2]);
	}
	else
		exit(printf("EC"));
}

static void	distributione(t_g *g, char **t)
{
	if (!ft_strcmp(t[0], "R"))
		stlen(t) != 3 || ocins("0123456789", t[1]) || ocins("0123456789", t[2])
		|| (g->res[0] = MIN(ft_atoi(t[1]), 2560)) <= 0 || (g->res[1] += MIN(
		ft_atoi(t[2]), 1440)) <= 0 || (g->checklist[0])++ ? exit(ps(ER)) : 0;
	else if (!ft_strcmp(t[0], "NO"))
		stlen(t) != 2 || !((*g).m.nt = mlx_xpm_file_to_image((*g).tb.p, t[1],
		&((*g).a), &((*g).a))) || (g->checklist[1])++ ? exit(ps(ET)) : 0;
	else if (!ft_strcmp(t[0], "EA"))
		stlen(t) != 2 || !((*g).m.eat = mlx_xpm_file_to_image((*g).tb.p, t[1],
		&((*g).a), &((*g).a))) || (g->checklist[2])++ ? exit(ps(ET)) : 0;
	else if (!ft_strcmp(t[0], "SO"))
		stlen(t) != 2 || !((*g).m.sot = mlx_xpm_file_to_image((*g).tb.p, t[1],
		&((*g).a), &((*g).a))) || (g->checklist[3])++ ? exit(ps(ET)) : 0;
	else if (!ft_strcmp(t[0], "WE"))
		stlen(t) != 2 || !((*g).m.wet = mlx_xpm_file_to_image((*g).tb.p, t[1],
		&((*g).a), &((*g).a))) || (g->checklist[4])++ ? exit(ps(ET)) : 0;
	else if (!ft_strcmp(t[0], "S"))
		stlen(t) != 2 || !((*g).m.st = mlx_xpm_file_to_image((*g).tb.p, t[1],
		&((*g).a), &((*g).a))) || (g->checklist[5])++ ? exit(ps(ET)) : 0;
	else
		distributitwo(g, t);
}

static int	mapcheck(t_g *g, size_t i, char *l, int f)
{
	if (l[0] != '1')
	{
		l[0] ? exit(ps(EC)) : 0;
		g->m.row && ocins("1 ", g->m.a[g->m.row - 1]) ? exit(ps(EM)) : 0;
		g->m.row ? (g->m.mend = 1) : 0;
		if (!f)
			return (1);
		return (2);
	}
	ft_array_realloc(&(*g).m.a, (*g).m.row + 2);
	g->m.col ? 0 : (g->m.col = ft_strlen(strdup_spe(l, ' ')));
	(((!f || !(*g).m.row) && ocins("1 ", l)) || l[ft_strlen(l) - 1]
	!= '1' || l[0] != '1' || ocins("120NEWS ", l) || (g->m.col &&
	g->m.col != ft_strlen(strdup_spe(l, ' '))) ? exit(printf(EM)) : 0);
	while (++i < ft_strlen(l))
		if (chrinstr("NESW", l[i]))
		{
			(*g).pe ? exit(printf(EM)) : 0;
			(*g).p = new_plr(i / 2, (*g).m, !(l[i] - 69) +
			!(l[i] - 83) * 2 + !(l[i] - 87) * 3);
			(l[i] = '0') && ((*g).pe++);
		}
	(*g).m.a[(*g).m.row++] = strdup_spe(l, ' ');
	(*g).m.a[(*g).m.row] = 0;
	return (0);
}

void		readdotcub(t_g *g, int fd)
{
	int			f;
	size_t		i;
	char		*l;
	static int	c = 0;

	while (((i = -1) || 1))
	{
		f = get_next_line(fd, &l);
		l = ft_strtrim(l, " ");
		g->m.mend && l[0] ? exit(ps(EC)) : 0;
		if (chrinstr("RNESWFC", l[0]) && c++ < 8)
			distributione(g, split_1space(l));
		else if (c == 8)
		{
			if ((i = mapcheck(g, i, l, f)) == 2)
				continue ;
		}
		else if (l[0])
			exit(ps(EC));
		if (!f || i == 1)
			break ;
	}
	!g->pe ? exit(printf(EM)) : 0;
	c != 8 ? exit(printf(EC)) : 0;
}
