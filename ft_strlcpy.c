/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:19:39 by arhallab          #+#    #+#             */
/*   Updated: 2020/01/03 17:46:55 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t s)
{
	size_t			i;

	i = 0;
	while (i + 1 < s && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (s)
		dst[i] = '\0';
	return (ft_strlen(src));
}
