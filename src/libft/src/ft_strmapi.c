/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:13:37 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/01 15:13:38 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen((char *)s);
	if (s && f)
	{
		str = malloc((sizeof(char) * len) + 1);
		if (str)
		{
			while (len > i)
			{
				str[i] = f(i, s[i]);
				i++;
			}
			str[i] = '\0';
			return (str);
		}
	}
	return (NULL);
}
