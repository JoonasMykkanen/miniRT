/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 06:52:30 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_ambient(t_data *data, t_color *color)
{
	t_ambient	ambient;

	ambient = data->scene.ambient;
	color->red = ambient.color.red * ambient.intensity;
	color->green = ambient.color.green * ambient.intensity;
	color->blue = ambient.color.blue * ambient.intensity;
	color->red *= data->obj.color.red / 255.0;
	color->green *= data->obj.color.green / 255.0;
	color->blue *= data->obj.color.blue / 255.0;
	data->pix.ambient = ambient.color;
}

static double	calculate_spot_light(t_data *data, t_vector point)
{
	t_vector	pos;
	double		d;

	pos = data->scene.light.position;
	data->pix.light_dir = normalize(subtract(pos, point));
	if (data->pix.obj_type == PLANE)
		data->pix.norm = data->scene.planes[data->pix.obj_idx].normal;
	else
		data->pix.norm = normalize(subtract(point, data->obj.point));
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}

// Using Blinn-Phong reflection model
static void	calculate_specular(t_data *data, t_color *specular, t_vector point)
{
	double		angle;
	double		intensity;
	t_vector	half;
	t_vector	pos;

	pos = data->scene.light.position;
	data->pix.light_dir = normalize(subtract(pos, point));
	data->pix.norm = normalize(subtract(data->scene.camera.position, point));
	half = vec_add(data->pix.light_dir, data->pix.norm);
	half = normalize(half);
	if (data->pix.obj_type == PLANE)
		data->pix.norm = data->scene.planes[data->pix.obj_idx].normal;
	else
		data->pix.norm = normalize(subtract(point, data->obj.point));
	angle = fmax(0.0, dot_product(data->pix.norm, half));
	intensity = pow(angle, data->obj.shine) * data->obj.specular;
	specular->red = intensity * 255;
	specular->green = intensity * 255;
	specular->blue = intensity * 255;
}

t_color	calculate_color(t_data *data, t_obj *obj, t_vector inter)
{
	t_color	specular;
	t_color	ambient;
	t_light	light;
	t_color	spot;
	double	d;

	light = data->scene.light;
	if (data->pix.obj_type == CYLINDER)
	{
		if (data->scene.cylinders[obj->idx].fcylinder == 0)
			d = calculate_body(data, inter, &data->scene.cylinders[obj->idx]);
		else
			d = calculate_cap(data, inter, &data->scene.cylinders[obj->idx]);
	}
	else
		d = calculate_spot_light(data, inter);
	calculate_ambient(data, &ambient);
	spotlight_effect(&light, obj, &spot, d);
	calculate_specular(data, &specular, inter);
	obj->color.red = (int)(ambient.red + spot.red + specular.red);
	obj->color.green = (int)(ambient.green + spot.green + specular.green);
	obj->color.blue = (int)(ambient.blue + spot.blue + specular.blue);
	clamp_colors(&obj->color);
	return (obj->color);
}
