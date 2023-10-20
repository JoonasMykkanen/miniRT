/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:09 by djames            #+#    #+#             */
/*   Updated: 2023/10/20 15:40:34 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_sphere(t_data *data, char **params)
{
	t_sphere	*ptr;
	int			*idx;

	idx = &data->scene.num_spheres;
	ptr = &data->scene.spheres[*idx];
	if (*idx >= MAX_OBJ)
		return (ERROR);
	if (arr_len(params) != 4)
		return (ERROR);
	if (assign_vector(&ptr->center, params[1], POSITION) == ERROR)
		return (ERROR);
	ptr->diameter = ft_atof(params[2]);
	if (check_size(ptr->diameter) == ERROR)
		return (ERROR);
	if (assign_color(&ptr->color, params[3]) == ERROR)
		return (ERROR);
	ptr->radius = ptr->diameter / 2;
	*idx += 1;
	return (OK);
}
