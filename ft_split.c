/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:30:38 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/26 21:51:09 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

static	int		sc(char *s, char c)
{
	int i;
	int a;

	i = -1;
	a = 0;
	while (1)
	{
		if ((++i != 0 && s[i] == c && s[i - 1] != '\0')
		|| (i != 0 && s[i] == '\0' && s[i - 1] != '\0'))
			a++;
		if (!(s[i]))
			break ;
		if (s[i] == c)
			s[i] = '\0';
	}
	return (a);
}

static	int		ss1(char *s)
{
	int i;
	int a;

	i = -1;
	a = 0;
	while (1)
	{
		if ((++i != 0 && s[i] == ' ' && s[i - 1] != '\0')
		|| (i != 0 && s[i] == '\0' && s[i - 1] != '\0'))
			a++;
		if (!(s[i]))
			break ;
		if (s[i] == ' ')
			s[i] = '\0';
		if (a && s[i + 1] != ' ')
			break ;
	}
	return (a + 1);
}

static	int		fill(char **tab, char *nw, int i, int b)
{
	if (!(tab[b] = malloc(sizeof(char) * (ft_strlen(&nw[i]) + 1))))
	{
		while (--b >= 0)
			free(tab[b]);
		free(tab);
		return (0);
	}
	ft_strlcpy(tab[b], &nw[i], ft_strlen(&nw[i]) + 1);
	return (1);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		a;
	int		b;
	char	**tab;
	char	*nw;

	if (!s)
		return (NULL);
	nw = ft_strdup(s);
	a = sc(nw, c);
	b = 0;
	i = -1;
	if (!(tab = (char **)malloc(sizeof(char *) * (a + 1))))
		return (NULL);
	while (b < a)
		if ((++i == 0 || !(nw[i - 1])) && nw[i])
		{
			if (!fill(tab, nw, i, b++))
				return (NULL);
			i += ft_strlen(&nw[i]) - 1;
		}
	free(nw);
	tab[b] = 0;
	return (tab);
}

char			**split_1space(char const *s)
{
	int		i;
	int		a;
	int		b;
	char	**tab;
	char	*nw;

	if (!s)
		return (NULL);
	if (s[0] == 'R')
		return (ft_split(s, ' '));
	nw = ft_strdup(s);
	a = ss1(nw);
	b = 0;
	i = -1;
	if (!(tab = (char **)malloc(sizeof(char *) * (a + 1))))
		return (NULL);
	while (b < a)
		if ((++i == 0 || !(nw[i - 1])) && nw[i])
			if (!fill(tab, nw, i, b++) || ((i += ft_strlen(&nw[i]) - 1) && 0))
				return (NULL);
	free(nw);
	tab[b] = 0;
	return (tab);
}
