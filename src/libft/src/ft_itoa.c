/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:54:30 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/25 12:54:31 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*translate(char *str, char rev_num[13], int neg, int i)
{
	int	l;

	l = 1;
	if (neg == 1)
	{
		i--;
		str[0] = '-';
	}
	else if (neg == 0)
	{	
		i--;
		l--;
	}
	while (i >= 0)
	{
		str[l] = rev_num[i];
		l++;
		i--;
	}
	if (neg == 1)
		l--;
	str[l] = '\0';
	return (str);
}

static void	handle_neg(char rev_num[13], long long *n, int *neg, int *i)
{
	if (*n <= -2147483648)
	{
		rev_num[1] = '8';
		*n = -214748364;
		*i += 1;
	}
	if (*n < 0)
	{
		*neg = 1;
		*n *= -1;
		*i += 1;
	}
}

char	*ft_itoa(long long n)
{
	int		i;
	int		neg;
	char	*str;
	char	rev_num[20];

	i = 0;
	neg = 0;
	handle_neg(rev_num, &n, &neg, &i);
	if (neg == 1)
		rev_num[0] = '-';
	while (n > 9)
	{
		rev_num[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	rev_num[i] = (n + '0');
	i++;
	rev_num[i] = ('\0');
	str = malloc(sizeof(char) * (ft_strlen(rev_num)) + 1);
	if (!str)
		return (NULL);
	str = translate(str, rev_num, neg, i);
	return (str);
}
