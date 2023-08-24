/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/24 13:52:21 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_ambient(t_data *data, char **params)
{
	t_ambient *ptr;

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
