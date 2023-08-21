/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:18:46 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/01 10:18:47 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_front(char *s1, char *set)
{
	int	len;
	int	trim;

	trim = 0;
	len = ft_strlen(s1);
	while (trim < len)
	{
		if (ft_strchr(set, s1[trim]) != NULL)
			trim++;
		else
			break ;
	}
	return (trim);
}

static int	trim_back(char *s1, char *set)
{
	int	len;
	int	trim;

	trim = 0;
	len = ft_strlen(s1);
	while (trim < len)
	{
		if (ft_strchr(set, s1[len - trim - 1]) != NULL)
			trim++;
		else
			break ;
	}
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int					f;
	int					b;
	char				*str;
	unsigned int		len;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	len = ft_strlen((char *)s1);
	b = trim_back((char *)s1, (char *)set);
	f = trim_front((char *)s1, (char *)set);
	str = malloc((sizeof(char) * (len - (b + f))) + 1);
	if (str)
	{
		len = len - (b + f);
		ft_strlcpy(str, s1 + f, len + 1);
		return (str);
	}
	return (NULL);
}
