/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gadgets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 00:59:21 by arhallab          #+#    #+#             */
/*   Updated: 2020/02/27 03:01:02 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

int		min(int a, int b)
{
	return (a < b ? a : b);
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

int		b(int a)
{
	return (a < 256 || a >= 0 ? 0 : 1);
}

double	dst(double x1, double x2, double y1, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}
