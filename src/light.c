/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:05:17 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/07 06:51:45 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_color(t_data *data, t_vector point, t_color color)
{
	double 	d;
	double	s;
	t_color	ambient;
	t_color	spot;
	
	d = calculate_spot_light(data, point);
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
	check_rgb_values(&color);
	return ft_color(color.red,color. green, color.blue, 0xff);
}

double	calculate_spot_light(t_data *data, t_vector point)
{
	double	d;

	data->pix.scaled_dir = vec_multis(data->scene.ray.dir, data->pix.closest_t);
	data->pix.hit_pos = subtract(data->scene.ray.orig, point);
	data->pix.hit_pos = vec_add(data->pix.hit_pos, data->pix.scaled_dir);
	data->pix.norm = normalize(data->pix.hit_pos);
	data->pix.light_dir = normalize(subtract(data->scene.light.position, data->pix.hit_pos));
	if (data->pix.obj_type == PLANE)
		d = fmax(dotProduct(data->scene.planes[data->pix.obj_idx].normal, data->pix.light_dir), 0.0);	
	else
		d = fmax(dotProduct(data->pix.norm, data->pix.light_dir), 0.0);	
	// TODO: keep testing without, if no issues, remove
	// if (d > 1)
	// 	d = 1;
	return (d);
}

void	check_rgb_values(t_color *color)
{
	if (color->red > 255)
		color->red = 255;
	if (color->green > 255)
		color->green = 255;
	if (color->blue > 255)
		color->blue = 255;
	if (color->red < 0)
		color->red = 0;
	if (color->green < 0)
		color->green = 0;
	if (color->blue < 0)
		color->blue = 0;
}
