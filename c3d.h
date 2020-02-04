/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:41:38 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/04 12:39:07 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _C3D_H
# define _C3D_H
# include <mlx.h>
# include <math.h>
# include "get_next_line.h"
# define ER "Error\nIn Resolution\n"
# define ET "Error\nIn Texture path\n"
# define ECF "Error\nWrong Color format\n"
# define EC "Error\nINVALID .cub\n"
# define EM "Error\nInvalid Map\n"

char			**ft_split(char const *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t s);
int				ft_atoi(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);

typedef struct	s_toolbox
{
	void		*p;
	void		*w;
	char		*i;
	int			*i_a;
	char		*bi;
	int			*bi_a;
}				t_tb;

typedef struct	s_map
{
	char		**a;
	size_t		col;
	size_t		row;
	int			offset[2];
	int			ts;
	char		*nt;
	int			*na;
	char		*sot;
	int			*soa;
	char		*eat;
	int			*eaa;
	char		*wet;
	int			*wea;
	char		*st;
	int			*sa;
	ssize_t		fc;
	ssize_t		cc;
}				t_m;

typedef struct	s_player
{
	double		p[2];
	int			s;
	int			ms;
	int 		rs;
	double		o;
	int			coll[2];
	double		t[4];
	int			w[4];
	int			spaaaaaace;
	int			lu;
	int			ld;
	int			lr;
	int			ll;
	
}				t_pl;

typedef struct	s_sprite
{
	int			p[2];
	double		dst;
}				t_s;

typedef struct	s_game
{
	int			res[2];
	t_tb		tb;
	t_pl		pl;
	int			pe;
	int			n_sp;
	t_m			m;
	int			yuzless;
	double		tmp[4];
	t_s			*sd;
	int			a;
	double 		dpp;
	double		sfr;
	double		sct[3];
	double		pi_6;
}				t_g;

#endif

			

