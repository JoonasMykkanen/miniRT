/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:53:50 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/27 15:53:51 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*ptr;

	i = 0;
	ch = c;
	ptr = (char *)s;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == ch)
		{
			return (&ptr[i]);
		}
		i++;
	}
	if (ch == '\0' && ptr[i] == '\0')
		return (&ptr[i]);
	return (NULL);
}
