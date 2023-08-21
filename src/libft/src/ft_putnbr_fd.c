/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:35:44 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/25 11:35:45 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	rev_num[12];

	i = 0;
	if (n <= -2147483648)
	{
		rev_num[0] = '8';
		i = 1;
		n = -214748364;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	while (n > 9)
	{
		rev_num[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	ft_putchar_fd((n + '0'), fd);
	while (i-- > 0)
		ft_putchar_fd(rev_num[i], fd);
}
