/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:55 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:31:58 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_light(t_data *data, char **params)
{
	t_light	*ptr;

	ptr = &data->scene.light;
	if (arr_len(params) != 4 || data->scene.status_light != false)
		return (ERROR);
	if (assign_vector(&ptr->position, params[1], POSITION) == ERROR)
		return (ERROR);
	ptr->brightness = ft_atof(params[2]);
	if (check_brightness(ptr->brightness) == ERROR)
		return (ERROR);
	if (assign_color(&ptr->color, params[3]) == ERROR)
		return (ERROR);
	data->scene.status_light = true;
	return (OK);
}
