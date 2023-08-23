/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 22:58:41 by joonasmykka      ###   ########.fr       */
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
	if (arr_len(params) != 4)
		return (ERROR);
	if (assign_vector(&ptr[*idx].center, params[1], POSITION) == ERROR)
		return (ERROR);
	ptr->diameter = ft_atof(params[2]);
	if (check_size(ptr->diameter) == ERROR)
		return (ERROR);
	// TODO: not sure if giving alpha 1 or 255 is correct.
	if (assign_color(&ptr[*idx].color, 255.0, params[3]) == ERROR)
		return (ERROR);
	*idx++;
	return (OK);
}
