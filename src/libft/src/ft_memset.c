/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:26:24 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:09:22 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int	i;

	i = 0;
	if (len > 0)
	{
		while (len > 0)
		{
			*((unsigned char *)b + i) = c;
			len--;
			i++;
		}
	}
	return (b);
}
