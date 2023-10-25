/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:03 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 11:23:00 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

int	create_obj_plane(t_data *data, char **params)
{
	t_plane	*ptr;
	int		*idx;

	idx = &data->scene.num_planes;
	ptr = &data->scene.planes[*idx];
	if (*idx >= MAX_OBJ)
		return (ERROR);
	if (arr_len(params) != 4)
		return (ERROR);
	if (assign_vector(&ptr->point, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&ptr->normal, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (assign_color(&ptr->color, params[3]) == ERROR)
		return (ERROR);
	*idx += 1;
	return (OK);
}
