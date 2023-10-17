/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:56:59 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 11:58:00 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

static void	init_values(int *integer, double *fract, double *div, int *sign)
{
	*sign = 1;
	*div = 10.0;
	*integer = 0;
	*fract = 0.0;
}

static int	handle_sign(int	*sign, char c)
{
	if (c == '-')
	{
		*sign = -1;
		return (0);
	}
	return (1);
}

double	ft_atof(char *str)
{
	double	fractal;
	double	divisor;
	int		integer;
	int		sign;

	init_values(&integer, &fractal, &divisor, &sign);
	while (*str == ' ')
		str++;
	if (handle_sign(&sign, *str) == 0)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		integer = integer * 10 + (*str - '0');
		str++;
	}
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			fractal = fractal + ((*str - '0') / divisor);
			divisor *= 10.0;
			str++;
		}
	}
	return ((double)sign * (integer + fractal));
}
