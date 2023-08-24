/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/24 13:29:19 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_plane(t_data *data, char **params)
{
	t_plane *ptr;
	int		*idx;

	idx = &data->scene.num_planes;
	ptr = &data->scene.planes[*idx];
	if (arr_len(params) != 4)
		return (ERROR);
	if (assign_vector(&ptr[*idx].point, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&ptr[*idx].normal, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (assign_color(&ptr[*idx].color, params[3]) == ERROR)
		return (ERROR);
	*idx++;
}


