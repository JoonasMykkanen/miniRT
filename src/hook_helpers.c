/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:38:45 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/17 12:43:11 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_camera(t_data *data, int mode, float delta)
{
	if (mode == HORIZONTAL) {
		data->scene.camera.angle += delta;
		data->scene.camera.position.x = data->scene.camera.R * cos(data->scene.camera.angle);
		data->scene.camera.position.z = data->scene.camera.R * sin(data->scene.camera.angle);
	}
	else if (mode == VERTICAL) {
		data->scene.camera.position.y += delta;
	}
	else if (mode == DEPTH) {
		data->scene.camera.position.z += delta;
	}
}
