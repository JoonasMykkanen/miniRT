/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:07 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:31:10 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_ambient(t_data *data, char **params)
{
	t_ambient	*ptr;

	ptr = &data->scene.ambient;
	if (arr_len(params) != 3 || data->scene.status_ambient != false)
		return (ERROR);
	if (check_number(params[1]) == ERROR)
		return (ERROR);
	ptr->intensity = ft_atof(params[1]);
	if (check_brightness(ptr->intensity) == ERROR)
		return (ERROR);
	if (assign_color(&ptr->color, params[2]) == ERROR)
		return (ERROR);
	data->scene.status_ambient = true;
	return (OK);
}
