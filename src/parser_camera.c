/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 11:04:22 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_camera(t_data *data, char **params)
{
	if (arr_len(params) != 4 || data->scene.status_camera != false)
		return (ERROR);
	
	return (OK);
}

