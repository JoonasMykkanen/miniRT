/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:21:11 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/29 19:21:12 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_c(va_list *args, int count)
{
	char	c;

	c = va_arg(*args, int);
	ft_putchar_fd(c, 1);
	return (++count);
}
