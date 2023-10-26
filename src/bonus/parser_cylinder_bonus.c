/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:39 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 12:37:01 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

int	create_obj_cylinder(t_data *data, char **params)
{
	t_cylinder	*ptr;
	int			*idx;

	idx = &data->scene[0].num_cylinders;
	ptr = &data->scene[0].cylinders[*idx];
	if (*idx >= MAX_OBJ)
		return (ERROR);
	if (arr_len(params) != 6)
		return (ERROR);
	if (assign_vector(&ptr->center, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&ptr->axis, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (check_number(params[3]) == ERROR)
		return (ERROR);
	ptr->diameter = ft_atof(params[3]);
	ptr->diameter /= 2;
	if (check_number(params[4]) == ERROR)
		return (ERROR);
	ptr->height = ft_atof(params[4]);
	if (assign_color(&ptr->color, params[5]) == ERROR)
		return (ERROR);
	*idx += 1;
	return (OK);
}
