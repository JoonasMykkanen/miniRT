/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:51:51 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/19 12:55:38 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
// #include <float.h>

int	check_color(int value)
{
	if (value >= 0 && value <= 255)
	{
		return (OK);
	}
	return (ERROR);
}

int	check_orientation(double value)
{
	if (value >= -1.0 && value <= 1.0)
		return (OK);
	return (ERROR);
}

int	check_size(double value)
{
	if (value > 0.0)
		return (OK);
	return (ERROR);
}

int	check_brightness(double value)
{
	if (value > 0.0 && value <= 1.0)
		return (OK);
	return (ERROR);
}

int	check_overflow(double value)
{
	if (value > FLT_MAX || value < -FLT_MAX)
		return (ERROR);
	return (OK);
}
