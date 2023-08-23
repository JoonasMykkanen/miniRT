/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:33:53 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 11:28:30 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static int	check_color_values(int r, int g, int b)
{
	if (check_color(r) == ERROR)
		return (ERROR);
	if (check_color(g) == ERROR)
		return (ERROR);
	if (check_color(b) == ERROR)
		return (ERROR);
	return (OK);
}

int	assign_color(void *target, float alpha, char *str)
{
	char	**colors;
	int		green;
	int		blue;
	int		red;

	colors = ft_split(str, ',');
	if (!colors || arr_len(colors) != 3)
	{
		free_arr(colors);
		return (ERROR);
	}
	red = ft_atoi(colors[0]);
	green = ft_atoi(colors[1]);
	blue = ft_atoi(colors[2]);
	free_arr(colors);
	if (check_color_values(red, green, blue) == ERROR)
		return (ERROR);
	*(int *)target = ft_color(red, green, blue, normalize_alpha(alpha));
	return (OK);
}
