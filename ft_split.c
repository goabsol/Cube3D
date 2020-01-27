/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:30:38 by arhallab          #+#    #+#             */
/*   Updated: 2020/01/03 17:43:36 by arhallab         ###   ########.fr       */
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
		|| (s[i] == '\0' && s[i - 1] != '\0'))
			a++;
		if (!(s[i]))
			break ;
		if (s[i] == c)
			s[i] = '\0';
	}
	return (a);
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

	if (!s || !(nw = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	ft_strlcpy(nw, s, ft_strlen(s) + 1);
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
