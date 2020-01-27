/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:18:59 by arhallab          #+#    #+#             */
/*   Updated: 2020/01/04 18:02:55 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ns;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	i = (size_t)start;
	if (!(ns = (char *)malloc(sizeof(s[i]) * (len + 1))))
		return (NULL);
	while (i < len + (size_t)start)
	{
		ns[i - (size_t)start] = s[i];
		i++;
	}
	*(ns + len) = '\0';
	return (ns);
}
