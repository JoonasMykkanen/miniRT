/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:50:19 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/27 16:50:21 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*ptr;

	ch = c;
	ptr = (char *)s;
	i = ft_strlen(ptr);
	while (i >= 0)
	{
		if (ptr[i] == ch)
		{
			return (&ptr[i]);
		}
		i--;
	}
	return (NULL);
}
