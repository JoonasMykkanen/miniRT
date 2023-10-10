/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:17:48 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/10 12:03:17 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_plane(t_data *data) 
{
	t_vector	intersect;
	t_plane		obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.planes[idx];
	intersect = vec_add(vec_multis(data->scene.ray.dir, data->pix.closest_t), data->scene.ray.orig);
	if (FIXED_PLANES)
	{
		
	}
	if (!is_in_shadow(intersect, data->scene.light.position, data, idx))
		data->pix.color = calculate_color(data, obj.point, obj.color, intersect);
}

void	draw_cylinder(t_data *data)
{
	t_vector	intersect;
	t_cylinder	obj;
	int			idx;
	t_vector luz;

	idx = data->pix.obj_idx;
	obj = data->scene.cylinders[idx];
	intersect = ray_at(data->scene.ray, data->pix.closest_t);
	luz = vec_multis(obj.axis, ((obj.height) / 2));
	luz = vec_add(obj.center, luz);
	if (!is_in_shadow(intersect, data->scene.light.position, data, idx))
	// if (data->pix.is_cap == 1)
	// 	data->pix.color = 0xff0000ff;
	// else
		//data->pix.color = calculate_color(data, obj.center, obj.color);
		data->pix.color = calculate_color(data, obj.axis, obj.color, intersect);
}
void	draw_sphere(t_data *data)
{
	t_vector	intersect;
	t_sphere	obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.spheres[idx];
	intersect = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(intersect, data->scene.light.position, data, idx))
		data->pix.color = calculate_color(data, obj.center, obj.color,intersect);
}

int	render_pixel(t_data *data, int x, int y)
{
	data->pix.closest_t = DBL_MAX;
	data->pix.color = 0x000000FF;
	data->pix.obj_type = NONE;
	update_ray(data, x, y);
	shoot_ray(data);
	if (data->pix.obj_type == PLANE)
		draw_plane(data);
	if (data->pix.obj_type == SPHERE)
		draw_sphere(data);
	// TODO CREATE LOGIC FOR BELOW
	if (data->pix.obj_type == CYLINDER)
		draw_cylinder(data);
	return (data->pix.color);
}