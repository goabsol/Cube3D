/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:41:38 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/24 08:47:08 by arhallab         ###   ########.fr       */
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
# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))
# define B(a) ((a) < 256 || (a) >= 0 ? 0 : 1)

typedef struct	s_toolbox
{
	void		*p;
	void		*w;
	char		*i;
	int			*i_a;
	char		*bi;
	int			*bi_a;
}				t_tb;

typedef struct	s_render_ctes
{
	int			wallh;
	int 		wtop;
	int			wbot;
	int			x1;
	int			x2;
	int			x3;
	int			x4;
	int			c1;
	double		c2;
	int			c;
}				t_rc;

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
	int			mend;
}				t_m;

typedef struct	s_player
{
	double		p[2];
	int			s;
	int			ms;
	int			rs;
	double		o;
	int			coll[2];
	double		t[4];
	int			w[4];
	int			spaaaaaace;
	int			lu;
	int			ld;
	int			lr;
	int			ll;
	int			escape;
}				t_pl;

typedef struct	s_sprite
{
	int			stop;
	int			sbot;
	int			c1;
	double		c2;
	int			x1;
	int			x2;
	int			co1;
	int			co2;
	int			co3;
	double		p[2];
	double		c[2];
	double		s[2];
	double		pcls;
	double		cte;
	double		dst;
	double		dfc;
	int			sh;
}				t_s;

typedef struct	s_game
{
	t_s			*sd;
	double		pi_6;
	double		dtr;
	int			checklist[8];
	int			res[2];
	t_tb		tb;
	t_pl		p;
	int			pe;
	int			n_sp;
	t_m			m;
	int			yzle;
	double		tmp[4];
	int			a;
	double		step[2];
	double		dpp;
	double		sfr;
	double		sct[3];
}				t_g;

char			**ft_split(char const *s, char c);
char			**split_1space(char const *s);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t s);
int				ft_atoi(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
int				ps(char *str);
t_g				new_game(void);
t_pl			new_plr(size_t x, t_m m, int a);
int				count(char *s, char c);
int				stlen(char **t);
int				ocins(char *c, const char *s);
int				ft_array_realloc(char ***p, size_t size);
int				t_s_array_realloc(t_s **p, size_t size);
void			sprite_rsort(t_s **a, int s);
int				kp(int k, t_pl *p);
int				kr(int k, t_pl *p);
int				hi(t_g *g);
void			dothestuff(t_pl p, t_g g);
char			*strdup_spe(char *s, char c);
void			readdotcub(t_g *g, int fd);
int				isnum(char *s);
void			raycast(t_g *g, int h, int w, t_pl p);
void			startingpoint(t_g *g, t_pl *p, double ray);

#endif
