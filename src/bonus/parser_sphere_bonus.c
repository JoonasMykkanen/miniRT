/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:09 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 12:35:47 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

int	create_obj_sphere(t_data *data, char **params)
{
	t_sphere	*ptr;
	int			*idx;

	idx = &data->scene[0].num_spheres;
	ptr = &data->scene[0].spheres[*idx];
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
