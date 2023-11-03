/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:29:02 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:09:48 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	l;

	i = 0;
	l = (int)dstsize;
	if (dstsize > 0)
	{
		while (dstsize > 1 && *(src + i) != '\0')
		{
			if (i == l)
			{
				i--;
				break ;
			}
			*(dst + i) = *(src + i);
			i++;
			dstsize--;
		}
		*(dst + i) = '\0';
	}
	while (*(src + i) != '\0')
		i++;
	return (i);
}
