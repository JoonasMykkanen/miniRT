/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 11:22:42 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

typedef int	(*t_check)(double);

static int	check_vector_values(t_vector *vec, char **xyz, t_check func)
{
	int	status;

	status = OK;
	vec->x = ft_atof(xyz[0]);
	if (func(vec->x) == ERROR || check_number(xyz[0]) == ERROR)
		status = ERROR;
	vec->y = ft_atof(xyz[1]);
	if (func(vec->y) == ERROR || check_number(xyz[1]) == ERROR)
		status = ERROR;
	vec->z = ft_atof(xyz[2]);
	if (func(vec->z) == ERROR || check_number(xyz[2]) == ERROR)
		status = ERROR;
	free_arr(xyz);
	return (status);
}

static int	choose_mode(t_vector *vec, char **xyz, int mode)
{
	int	status;

	status = ERROR;
	if (mode == POSITION)
		status = check_vector_values(vec, xyz, check_overflow);
	if (mode == ORIENTATION)
	{
		status = check_vector_values(vec, xyz, check_orientation);
		if ((vec->x == 0 && vec->y == 0) && vec->z == 0)
			status = ERROR;
	}
	return (status);
}

int	assign_vector(void *target, char *str, int mode)
{
	char		**xyz;
	t_vector	*vec;

	vec = (t_vector *)target;
	xyz = ft_split(str, ',');
	if (!xyz)
		return (ERROR);
	if (arr_len(xyz) != 3)
	{
		free_arr(xyz);
		return (ERROR);
	}
	if (choose_mode(vec, xyz, mode) == ERROR)
		return (ERROR);
	return (OK);
}

static int	check_color_values(int r, int g, int b, char **str)
{
	if (check_color(r) == ERROR || check_number(str[0]) == ERROR)
		return (ERROR);
	if (check_color(g) == ERROR || check_number(str[1]) == ERROR)
		return (ERROR);
	if (check_color(b) == ERROR || check_number(str[2]) == ERROR)
		return (ERROR);
	return (OK);
}

int	assign_color(void *target, char *str)
{
	char	**colors;
	t_color	*ptr;

	ptr = (t_color *)target;
	colors = ft_split(str, ',');
	if (!colors)
		return (ERROR);
	if (arr_len(colors) != 3)
	{
		free_arr(colors);
		return (ERROR);
	}
	ptr->red = ft_atoi(colors[0]);
	ptr->green = ft_atoi(colors[1]);
	ptr->blue = ft_atoi(colors[2]);
	if (check_color_values(ptr->red, ptr->green, ptr->blue, colors) == ERROR)
	{
		free_arr(colors);
		return (ERROR);
	}
	free_arr(colors);
	return (OK);
}
