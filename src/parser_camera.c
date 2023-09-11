/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/11 12:05:06 by jmykkane         ###   ########.fr       */
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
	*fov = value * M_PI / 180.0f;
	return (OK);
}

int	create_obj_camera(t_data *data, char **params)
{
	t_camera *ptr;

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

