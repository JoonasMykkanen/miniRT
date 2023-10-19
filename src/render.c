/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:31 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:32:34 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	draw_plane(t_data *data)
{
	t_vector	inter;

	inter = vec_add(vec_multis(data->scene.ray.dir, data->pix.closest_t),
			data->scene.ray.orig);
	if (!is_in_shadow(inter, data->scene.light.position, data, data->obj.idx))
		data->pix.color = calculate_color(data, &data->obj, inter);
}

static void	draw_cylinder(t_data *data)
{
	t_vector	inter;

	inter = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(inter, data->scene.light.position, data, data->obj.idx))
		data->pix.color = calculate_color(data, &data->obj, inter);
}

static void	draw_sphere(t_data *data)
{
	t_vector	inter;

	inter = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(inter, data->scene.light.position, data, data->obj.idx))
		data->pix.color = calculate_color(data, &data->obj, inter);
}

int	render_pixel(t_data *data, int x, int y)
{
	reset_pix(&data->pix);
	update_ray(data, x, y);
	shoot_ray(data);
	if (data->obj.type == PLANE)
		draw_plane(data);
	if (data->obj.type == SPHERE)
		draw_sphere(data);
	if (data->obj.type == CYLINDER)
		draw_cylinder(data);
	return (data->pix.color);
}
