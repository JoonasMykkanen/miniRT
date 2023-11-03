/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:15 by djames            #+#    #+#             */
/*   Updated: 2023/11/03 11:11:21 by jmykkane         ###   ########.fr       */
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
	if (value > 179)
		value = 179;
	*fov = value * M_PI / 180.0f;
	return (OK);
}

int	create_obj_camera(t_data *data, char **params)
{
	t_camera	*ptr;

	ptr = &data->scene[0].camera;
	if (arr_len(params) != 4 || data->scene[0].status_camera != false)
		return (ERROR);
	if (assign_vector(&ptr->position, params[1], POSITION) == ERROR)
		return (ERROR);
	if (assign_vector(&ptr->orientation, params[2], ORIENTATION) == ERROR)
		return (ERROR);
	if (assign_fov(&ptr->fov, params[3]) == ERROR)
		return (ERROR);
	if (ptr->fov == 180)
		ptr->fov -= EPSILON;
	data->scene[0].status_camera = true;
	return (OK);
}
