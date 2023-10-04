/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:17:48 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/04 06:42:50 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calculate_spot_light(t_data *data, t_vector point)
{
	double	d;

	data->pix.scaled_dir = vec_multis(data->scene.ray.dir, data->pix.closest_t);
	data->pix.hit_pos = subtract(data->scene.ray.orig, point);
	data->pix.hit_pos = vec_add(data->pix.hit_pos, data->pix.scaled_dir);
	data->pix.norm = normalize(data->pix.hit_pos);
	data->pix.light_dir = normalize(subtract(data->scene.light.position, data->pix.hit_pos));
	d = fmax(dotProduct(data->pix.norm, data->pix.light_dir), 0.0);	
	return (d);
}

int	calculate_color(t_data *data, t_vector point, t_color color)
{
	double d;
	
	d = calculate_spot_light(data, point);

	double ambientR = data->scene.ambient.color.red * data->scene.ambient.intensity;
	double ambientG = data->scene.ambient.color.green * data->scene.ambient.intensity;
	double ambientB = data->scene.ambient.color.blue * data->scene.ambient.intensity;

	ambientR *= color.red / 255.0;
	ambientG *= color.green / 255.0;
	ambientB *= color.blue / 255.0;

	double spotR = (d * data->scene.light.brightness * data->scene.light.color.red) * color.red / 255.0;
	double spotG = (d * data->scene.light.brightness * data->scene.light.color.green) *  color.green / 255.0;
	double spotB = (d * data->scene.light.brightness * data->scene.light.color.blue) * color.blue / 255.0;

	color.red = (int)(ambientR + spotR);
	color.green = (int)(ambientG + spotG);
	color.blue = (int)(ambientB + spotB);

	if (color.red > 255) color.red = 255;
	if (color.green > 255) color.green = 255;
	if (color.blue > 255) color.blue = 255;

	if (color.red < 0) color.red = 0;
	if (color.green < 0) color.green = 0;
	if (color.blue < 0) color.blue = 0;
	
	return ft_color(color.red,color. green, color.blue, 0xff);
}

void draw_plane(t_data *data) 
{
	t_plane		obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.planes[idx];
	data->pix.color = calculate_color(data, obj.point, obj.color);
}

void	draw_sphere(t_data *data)
{
	t_sphere	obj;
	int			idx;

	idx = data->pix.obj_idx;
	obj = data->scene.spheres[idx];
	data->pix.color = calculate_color(data, obj.center, obj.color);
}

int	render_pixel(t_data *data, int x, int y)
{
	data->pix.closest_t = DBL_MAX;
	data->pix.color = 0x000000ff;
	data->pix.obj_type = NONE;
	update_ray(data, x, y);
	shoot_ray(data);
	if (data->pix.obj_type == PLANE)
		draw_plane(data);
	if (data->pix.obj_type == SPHERE)
		draw_sphere(data);
	// TODO CREATE LOGIC FOR BELOW
	// if (data->pix.obj_type == CYLINDER)
		// draw_cylinder(data);
	return (data->pix.color);
}