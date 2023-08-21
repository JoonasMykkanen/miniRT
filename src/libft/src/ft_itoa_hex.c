/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:49:41 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/24 14:50:09 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_hex(unsigned long long num)
{
	int		i;
	int		temp;
	char	*str;
	char	buf[17];

	i = 0;
	if (num == 0)
		return (0);
	while (num != 0)
	{
		temp = num % 16;
		if (temp < 10)
			buf[i++] = (char)temp + 48;
		else
			buf[i++] = (char)temp + 87;
		num = num / 16;
	}
	temp = -1;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	while (--i >= 0)
		str[++temp] = buf[i];
	str[temp + 1] = '\0';
	return (str);
}
