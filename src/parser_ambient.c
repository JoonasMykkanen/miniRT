/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 11:29:10 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_ambient(t_data *data, char **params)
{
	if (arr_len(params) != 3 || data->scene.status_ambient != false)
		return (ERROR);
	data->scene.ambient.intensity = ft_atof(params[1]);
	if (check_brightness(data->scene.ambient.intensity) == ERROR)
		return (ERROR);
	if (assign_color(
			&data->scene.ambient.color,
			data->scene.ambient.intensity,
			params[2]) == ERROR)
		return (ERROR);
	data->scene.status_ambient = true;
	return (OK);
}
