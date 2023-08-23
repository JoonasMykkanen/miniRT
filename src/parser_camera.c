/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 14:21:58 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static int	assign_fov(int *fov, char *str)
{
	int		value;

	if (check_number(str) == ERROR)
		return (ERROR);
	value = ft_atoi(str);
	if (value < 0 || value > 180)
		return (ERROR);
	*fov = value;
	return (OK);
}

int	create_obj_camera(t_data *data, char **params)
{
	if (arr_len(params) != 4 || data->scene.status_camera != false)
		return (ERROR);
	if (assign_vector(&data->scene.camera.position, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&data->scene.camera.orientation, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (assign_fov(&data->scene.camera.fov, params[3]) == ERROR)
		return (ERROR);
	data->scene.status_camera = true;
	return (OK);
}

