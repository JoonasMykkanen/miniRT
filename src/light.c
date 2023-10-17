/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:05:17 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 11:12:03 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calculate_body(t_data *data, t_vector inter, t_vector axis,
		t_vector center)
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
static double	calculate_cap(t_data *data, t_vector inter, t_vector axis,
		t_vector center, double r)
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

static double	calculate_spot_light(t_data *data, t_vector point)
{
	double	d;

	data->pix.light_dir = normalize(subtract(data->scene.light.position,
			point));
	if (data->pix.obj_type == PLANE)
		data->pix.norm = data->scene.planes[data->pix.obj_idx].normal;
	else
		data->pix.norm = normalize(subtract(point, data->obj.point));
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}

static void	calculate_ambient(t_data *data, t_color *color)
{
	color->red = data->scene.ambient.color.red * data->scene.ambient.intensity;
	color->green = data->scene.ambient.color.green * data->scene.ambient.intensity;
	color->blue = data->scene.ambient.color.blue * data->scene.ambient.intensity;
	color->red *= data->obj.color.red / 255.0;
	color->green *= data->obj.color.green / 255.0;
	color->blue *= data->obj.color.blue / 255.0;
}

int	calculate_color(t_data *data, t_obj *obj, t_vector inter)
{
	t_color		ambient;
	t_light		light;
	t_color		spot;
	double		d;

	light = data->scene.light;
	if (data->pix.obj_type == CYLINDER)
	{
		if (!data->pix.cap)
			d = calculate_body(data, inter, obj->axis, obj->point);
		else
			d = calculate_cap(data, inter, obj->axis, obj->point, obj->radius);
	}
	else
		d = calculate_spot_light(data, inter);
	calculate_ambient(data, &ambient);
	spot.red = (d * light.brightness * light.color.red) * obj->color.red / 255.0;
	spot.green = (d * light.brightness* light.color.green) * obj->color.green / 255.0;
	spot.blue = (d * light.brightness* light.color.blue) * obj->color.blue / 255.0;
	obj->color.red = (int)(ambient.red + spot.red);
	obj->color.green = (int)(ambient.green + spot.green);
	obj->color.blue = (int)(ambient.blue + spot.blue);
	clamp_colors(&obj->color);
	return (ft_color(obj->color.red, obj->color.green, obj->color.blue, 0xff));
}

