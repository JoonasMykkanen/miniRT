/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:40:44 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/25 10:40:46 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*wrte(char *str, char const *s1, char const *s2)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s1[i] != '\0')
	{
		str[l] = s1[i];
		i++;
		l++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[l] = s2[i];
		i++;
		l++;
	}
	str[l] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*str;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * ((l1 + l2) + 1));
		if (str == NULL)
			return (NULL);
		str = wrte(str, s1, s2);
		return (str);
	}
	return (NULL);
}
