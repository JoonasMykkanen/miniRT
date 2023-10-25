/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:15 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 11:22:24 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

static int	assign_fov(float *fov, char *str)
{
	int	value;

	if (check_number(str) == ERROR)
		return (ERROR);
	value = ft_atoi(str);
	if (value < 0 || value > 180)
		return (ERROR);
	*fov = value * M_PI / 180.0f;
	return (OK);
}

int	create_obj_camera(t_data *data, char **params)
{
	t_camera	*ptr;

	ptr = &data->scene.camera;
	if (arr_len(params) != 4 || data->scene.status_camera != false)
		return (ERROR);
	if (assign_vector(&ptr->position, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&ptr->orientation, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (assign_fov(&ptr->fov, params[3]) == ERROR)
		return (ERROR);
	data->scene.status_camera = true;
	return (OK);
}
