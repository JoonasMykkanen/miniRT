/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:28:08 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:09:14 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	ch;
	void			*ptr;
	void			*src;

	i = 0;
	ch = c;
	src = (void *)s;
	while (n > 0)
	{
		if (*((unsigned char *)s + i) == ch)
		{
			ptr = &src[i];
			return (ptr);
		}
		n--;
		i++;
	}
	return (NULL);
}
