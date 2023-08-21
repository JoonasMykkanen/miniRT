/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:23:28 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/29 19:23:33 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	choose_conversion(va_list *args, char var, int count)
{
	if (var == 'c')
		count = convert_c(args, count);
	else if (var == 's')
		count = convert_s(args, count);
	else if (var == 'd' || var == 'i')
		count = convert_d_i(args, count);
	else if (var == 'u')
		count = convert_u(args, count);
	else if (var == 'p')
		count = convert_p(args, count);
	else if (var == 'x')
		count = convert_x(args, count);
	else if (var == 'X')
		count = convert_xx(args, count);
	else if (var == '%')
		count = convert_precentage(count);
	return (count);
}

static int	print_out(const char *s, va_list *args, int count)
{
	int		i;
	int		mode;

	i = -1;
	mode = 0;
	while (s[++i] != '\0')
	{
		if (mode == 0)
		{
			if (s[i] == '%')
				mode = 1;
			else
			{
				ft_putchar_fd(s[i], 1);
				count++;
			}
		}
		else if (mode == 1)
		{
			mode = 0;
			count = choose_conversion(args, s[i], count);
		}
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, s);
	count = print_out(s, &args, count);
	va_end(args);
	return (count);
}
