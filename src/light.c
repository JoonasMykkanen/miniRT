/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/21 08:16:24 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Calculating light for cylinder body
static double	calculate_body(t_data *data, t_vector inter, t_cylinder *cyl)
{
	t_vector	vec_inter;
	t_vector	axis_point;
	double		s;
	double		d;

	vec_inter = subtract(inter, cyl->center);
	s = dot_product(vec_inter, cyl->axis) / dot_product(cyl->axis, cyl->axis);
	axis_point = vec_add(cyl->center, vec_multis(cyl->axis, s));
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = normalize(data->pix.light_dir);
	data->pix.norm = subtract(inter, axis_point);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}

// Calculate ligth for cylinder caps
static double	calculate_cap(t_data *data, t_vector inter, t_cylinder *cyl)
{
	t_vector	opposite;
	double		d;

	opposite = cyl->axis;
	if (cyl->fcylinder == 2)
		opposite = vec_multis(cyl->axis, -1);
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = vec_multis(data->pix.light_dir, -1);
	data->pix.light_dir = normalize(data->pix.light_dir);
	data->pix.norm = vec_multis(opposite, -1.0f);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.light_dir, data->pix.norm), 0.0);
	return (d);
}


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
	
	// Light dir
	pos = data->scene.light.position;
	data->pix.light_dir = normalize(subtract(pos, point));

	// View dir
	data->pix.norm = normalize(subtract(data->scene.camera.position, point));

	// Half dir
	half = vec_add(data->pix.light_dir, data->pix.norm);
	half = normalize(half);

	// Normal of the hit
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

int	calculate_color(t_data *data, t_obj *obj, t_vector inter)
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
	return (ft_color(obj->color.red, obj->color.green, obj->color.blue, 0xff));
}
