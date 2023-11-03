/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:09:51 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:09:16 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int					i;
	const unsigned char	*src1;
	const unsigned char	*src2;

	i = 0;
	src1 = (const unsigned char *)s1;
	src2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (--n > 0)
	{
		if (src1[i] != src2[i])
		{
			return (src1[i] - src2[i]);
		}
		i++;
	}
	if (src1[i] != src2[i])
		return (src1[i] - src2[i]);
	return (0);
}
