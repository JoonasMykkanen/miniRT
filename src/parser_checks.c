/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:51:51 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 11:01:55 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include <float.h>

int	check_color(int	value)
{
	if (value >= 0 && value <= 255)
		return (OK);
	return (ERROR);
}
int	check_value(float value)
{
	if (value >= -1.0 && value <= 1.0)
		return (OK);
	return (ERROR);
}

int	check_size(float value)
{
	if (value > 0.0)
		return (OK);
	return (ERROR);
}

int	check_brightness(float value)
{
	if (value >= 0.0 && value <= 1.0)
		return (OK);
	return (ERROR);
}

int	check_overflow(double value)
{
	if (value > FLT_MAX || value < FLT_MIN)
		return (ERROR);
	return (OK);
}
