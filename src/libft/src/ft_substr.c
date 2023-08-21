/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:57:26 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/25 09:57:27 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test_max(char const *s, int start)
{
	int	total;

	total = ft_strlen(s) - start;
	return (total);
}

static char	*check_overflow(const char *s, size_t start)
{
	char	*str;

	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		max;
	char		*str;

	i = 0;
	if (!s)
		return (NULL);
	max = test_max(s, start);
	str = check_overflow(s, start);
	if (start >= ft_strlen(s))
		return (str);
	if (max > len)
		max = len;
	str = (char *)malloc((sizeof(char) * max) + 1);
	if (!str)
		return (NULL);
	while (len > 0 && i < max)
	{
		str[i] = s[start + i];
		len--;
		i++;
	}
	str[i] = '\0';
	return (str);
}
