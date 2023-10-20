/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:39 by djames            #+#    #+#             */
/*   Updated: 2023/10/20 14:37:31 by jmykkane         ###   ########.fr       */
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
	if (idx >= MAX_OBJ)
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
	if (check_number(params[4]) == ERROR)
		return (ERROR);
	ptr->height = ft_atof(params[4]);
	if (assign_color(&ptr->color, params[5]) == ERROR)
		return (ERROR);
	*idx += 1;
	return (OK);
}
