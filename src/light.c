/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:05:17 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 10:27:49 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clamp_colors(t_color *color)
{
	if (color->red < 0)
		color->red = 0;
	if (color->green < 0)
		color->green = 0;
	if (color->blue < 0)
		color->blue = 0;
	if (color->red > 255)
		color->red = 255;
	if (color->green > 255)
		color->green = 255;
	if (color->blue > 255)
		color->blue = 255;
}

double calculate_body(t_data *data, t_vector inter, t_vector axis, t_vector center)
{
	t_vector	vec_inter;
	t_vector	axis_point;
	double		scalar;
	double		d;

	vec_inter = subtract(inter, center);
	scalar = dot_product(vec_inter, axis) / dot_product(axis, axis);
	axis_point = vec_add(center, vec_multis(axis, scalar));
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = normalize(data->pix.light_dir);
	data->pix.norm = subtract(inter, axis_point);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}
double calculate_cap(t_data *data, t_vector inter, t_vector axis, t_vector center, double r)
{
	double	d;
	
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = normalize(data->pix.light_dir);
	if (data->pix.cap == TOP)
		data->pix.norm = axis;
	else
		data->pix.norm = vec_multis(axis, -1.0f);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}

int	calculate_color(t_data *data, t_vector axis, t_color color, t_vector inter, t_vector center, double r)
{
	t_color	ambient;
	t_color	spot;
	double 	d;
	
	if(data->pix.obj_type != CYLINDER)
		d = calculate_spot_light(data, inter);
	else
	{
		if (!data->pix.cap)
			d = calculate_body(data, inter, axis, center);
		else 
			d = calculate_cap(data, inter, axis, center, r);
	}
	ambient.red = data->scene.ambient.color.red * data->scene.ambient.intensity;
	ambient.green = data->scene.ambient.color.green * data->scene.ambient.intensity;
	ambient.blue = data->scene.ambient.color.blue * data->scene.ambient.intensity;
	ambient.red *= color.red / 255.0;
	ambient.green *= color.green / 255.0;
	ambient.blue *= color.blue / 255.0;
	spot.red = (d * data->scene.light.brightness * data->scene.light.color.red) * color.red / 255.0;
	spot.green = (d * data->scene.light.brightness * data->scene.light.color.green) *  color.green / 255.0;
	spot.blue = (d * data->scene.light.brightness * data->scene.light.color.blue) * color.blue / 255.0;
	color.red = (int)(ambient.red + spot.red);
	color.green = (int)(ambient.green + spot.green);
	color.blue = (int)(ambient.blue + spot.blue);
	clamp_colors(&color);
	return (ft_color(color.red, color. green, color.blue, 0xff));
}

double	calculate_spot_light(t_data *data, t_vector point)
{
	double	d;

	data->pix.light_dir = normalize(subtract(data->scene.light.position, point));
	if (data->pix.obj_type == PLANE)
		data->pix.norm = data->scene.planes[data->pix.obj_idx].normal;
	else
		data->pix.norm = normalize(subtract(point, data->scene.spheres[data->pix.obj_idx].center));
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}
