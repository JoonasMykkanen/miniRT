/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/24 13:28:39 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_cylinder(t_data *data, char **params)
{
	t_cylinder	*ptr;
	int			*idx;

	idx = &data->scene.num_cylinders;
	ptr = &data->scene.cylinders[*idx];

	if (arr_len(params) != 6)
		return (ERROR);
	if (assign_vector(&ptr->center, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&ptr->axis, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (check_number(params[3]) == ERROR)
		return (ERROR);
	ptr->diameter = ft_atof(params[3]);
	if (check_number(params[4]) == ERROR)
		return (ERROR);
	ptr->height = ft_atof(params[4]);
	if (assign_color(&ptr[*idx].color, params[3]) == ERROR)
		return (ERROR);
	*idx++;
	return (OK);
}

