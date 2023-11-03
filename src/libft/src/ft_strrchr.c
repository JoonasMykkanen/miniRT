/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:50:19 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:01 by djames           ###   ########.fr       */
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
