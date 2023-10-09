/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:17:48 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/09 12:07:51 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void draw_plane(t_data *data) 
{
	t_vector	intersect;
	t_plane		obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.planes[idx];
	intersect = vec_add(vec_multis(data->scene.ray.dir, data->pix.closest_t), data->scene.ray.orig);
	if (!is_in_shadow(intersect, data->scene.light.position, data, idx))
		data->pix.color = calculate_color(data, obj.point, obj.color);
}

static void	draw_cylinder(t_data *data)
{
	t_vector	intersect;
	t_cylinder	obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.cylinders[idx];
	intersect = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(intersect, data->scene.light.position, data, idx))
		data->pix.color = calculate_color(data, obj.center, obj.color);
}
static void	draw_sphere(t_data *data)
{
	t_vector	intersect;
	t_sphere	obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.spheres[idx];
	intersect = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(intersect, data->scene.light.position, data, idx))
		data->pix.color = calculate_color(data, obj.center, obj.color);
}

int	render_pixel(t_data *data, int x, int y)
{
	reset_pix(&data->pix);
	update_ray(data, x, y);
	shoot_ray(data);
	if (data->pix.obj_type == PLANE)
		draw_plane(data);
	if (data->pix.obj_type == SPHERE)
		draw_sphere(data);
	if (data->pix.obj_type == CYLINDER)
		draw_cylinder(data);
	return (data->pix.color);
}