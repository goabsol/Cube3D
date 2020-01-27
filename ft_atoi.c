/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 07:13:31 by arhallab          #+#    #+#             */
/*   Updated: 2020/01/03 18:15:30 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		ft_atoi(const char *s)
{
	int					i;
	long long	val;
	int					sign;

	sign = 1;
	i = -1;
	val = 0;
	while (s[++i] != '\0')
	{
		if ((s[i] > '/' && s[i] < ':') || s[i] == '-' || s[i] == '+')
		{
			(s[i] == '+' || s[i] == '-') && (sign = (s[i++] == '-' ? -1 : 1));
			while (s[i] > '/' && s[i] < ':')
			{
				if (val * 10 + s[i] - 48 > 9223372036854775807
					|| val * 10 + s[i] - 48 < -9223372036854775807LL - 1)
					return ((sign == -1 ? 0 : -1));
				val = val * 10 + s[i++] - 48;
			}
			return ((int)val * sign);
		}
		else if (s[i] != ' ' && (s[i] < 9 || s[i] > 13))
			return ((int)val * sign);
	}
	return ((int)val * sign);
}
