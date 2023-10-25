/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:23 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 11:22:32 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

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
