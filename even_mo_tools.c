/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_mo_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:43:07 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/24 07:42:07 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		ps(char *str)
{
	if (!str)
		return (0);
	while (*str)
		write(2, (void *)str++, 1);
	return (1);
}

int		isnum(char *s)
{
	int		i;
	int		f1;
	int		f2;

	i = -1;
	f1 = 0;
	f2 = 0;
	while (s && s[++i])
	{
		if (s[i] == ' ')
			continue ;
		if (!chrinstr(" 0123456789", s[i]) ||
		(f1 && f2 && chrinstr("0123456789", s[i])))
			return (0);
		if (chrinstr("0123456789", s[i]))
			f1 = 1;
		if (s[i] == ' ')
			f2 = 1;
		i++;
	}
	return (1);
}
