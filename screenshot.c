/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:02:40 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/29 00:26:54 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static t_rgb	colorconverter(int hexvalue)
{
	t_rgb		rgbcolor;

	rgbcolor.r = ((hexvalue >> 16) & 0xFF);
	rgbcolor.g = ((hexvalue >> 8) & 0xFF);
	rgbcolor.b = ((hexvalue) & 0xFF);
	return (rgbcolor);
}

static void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*ndest;
	const char		*nsrc;
	unsigned int	i;

	i = 0;
	ndest = (char*)dest;
	nsrc = (const char*)src;
	if (!(dest || src))
		return ((char*)NULL);
	while (i < (unsigned int)n)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return ((char*)dest);
}

static void		screen_init(t_g *g, unsigned char *header)
{
	g->scr.r[0] = g->res[0];
	g->scr.r[1] = g->res[1];
	g->scr.bitcount = 24;
	g->scr.w_in_bytes = ((g->scr.r[0] *
	g->scr.bitcount + 31) / 32) * 4;
	g->scr.imagesize = g->scr.w_in_bytes * g->scr.r[1];
	g->scr.bisize = 40;
	g->scr.bfoffbits = 54;
	g->scr.filesize = 54 + g->scr.imagesize;
	g->scr.biplanes = 1;
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &(g->scr.filesize), 4);
	ft_memcpy(header + 10, &(g->scr.bfoffbits), 4);
	ft_memcpy(header + 14, &(g->scr.bisize), 4);
	ft_memcpy(header + 18, &(g->scr.r[0]), 4);
	ft_memcpy(header + 22, &(g->scr.r[1]), 4);
	ft_memcpy(header + 26, &(g->scr.biplanes), 2);
	ft_memcpy(header + 28, &(g->scr.bitcount), 2);
	ft_memcpy(header + 34, &(g->scr.imagesize), 4);
}

static void		scr_g(t_g *g, int x)
{
	t_rgb	color;

	color = colorconverter(g->tb.bi_a[g->scr.row *
	g->scr.r[0] + g->scr.col]);
	g->scr.buf[x * g->scr.w_in_bytes
	+ g->scr.col * 3 + 0] = color.b;
	g->scr.buf[x * g->scr.w_in_bytes
	+ g->scr.col * 3 + 1] = color.g;
	g->scr.buf[x * g->scr.w_in_bytes
	+ g->scr.col * 3 + 2] = color.r;
}

int				screen(t_g *g)
{
	int				x;
	int				i;

	i = 0;
	while (i < 54)
		g->scr.header[i++] = 0;
	screen_init(g, g->scr.header);
	g->scr.buf = malloc((g->scr.imagesize));
	x = 0;
	g->scr.row = g->scr.r[1];
	while (--g->scr.row >= 0)
	{
		g->scr.col = -1;
		while (++g->scr.col < g->scr.r[0])
			scr_g(g, x);
		x++;
	}
	g->scr.fd = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(g->scr.fd, g->scr.header, 54);
	write(g->scr.fd, (char*)g->scr.buf, g->scr.imagesize);
	close(g->scr.fd);
	free(g->scr.buf);
	return (0);
}
