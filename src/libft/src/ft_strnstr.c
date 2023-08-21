/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:18:13 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/01 10:18:15 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_match(char *haystack, char *needle, int i, int min)
{
	int		l;

	l = 0;
	while (min > 0)
	{
		if (haystack[i] != needle[l])
			return (0);
		else
		{
			i++;
			l++;
			min--;
		}
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	int		i;
	int		min;
	int		found;

	i = 0;
	found = 0;
	min = ft_strlen((char *)needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (n > 0 && haystack[i] != '\0')
	{	
		if (min > (int)n)
			return (NULL);
		if (haystack[i] == needle[0])
		{
			found = check_match((char *)haystack, (char *)needle, i, min);
			if (found == 1)
				return ((char *)&haystack[i]);
		}
		i++;
		n--;
	}
	return (NULL);
}
