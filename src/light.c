/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:05:17 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 11:35:23 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	calculate_body(t_data *data, t_vector inter, t_obj *cyl)
{
	t_vector	vec_inter;
	t_vector	axis_point;
	double		s;
	double		d;

	vec_inter = subtract(inter, cyl->point);
	s = dot_product(vec_inter, cyl->axis) / dot_product(cyl->axis, cyl->axis);
	axis_point = vec_add(cyl->point, vec_multis(cyl->axis, s));
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = normalize(data->pix.light_dir);
	data->pix.norm = subtract(inter, axis_point);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}

static double	calculate_cap(t_data *data, t_vector inter, t_obj *cyl)
{
	double	d;

	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = normalize(data->pix.light_dir);
	if (data->pix.cap == TOP)
		data->pix.norm = cyl->axis;
	else
		data->pix.norm = vec_multis(cyl->axis, -1.0f);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
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

static void	calculate_ambient(t_data *data, t_color *color)
{
	t_ambient	ambient;

	ambient = data->scene.ambient;
	color->red = ambient.color.red * ambient.intensity;
	color->green = ambient.color.green * ambient.intensity;
	color->blue = ambient.color.blue * ambient.intensity;
	color->red *= data->obj.color.red / 255.0;
	color->green *= data->obj.color.green / 255.0;
	color->blue *= data->obj.color.blue / 255.0;
}

int	calculate_color(t_data *data, t_obj *obj, t_vector inter)
{
	t_color	ambient;
	t_light	light;
	t_color	spot;
	double	d;

	light = data->scene.light;
	if (data->pix.obj_type == CYLINDER)
	{
		if (!data->pix.cap)
			d = calculate_body(data, inter, obj);
		else
			d = calculate_cap(data, inter, obj);
	}
	else
		d = calculate_spot_light(data, inter);
	calculate_ambient(data, &ambient);
	spotlight_effect(&light, obj, &spot, d);
	obj->color.red = (int)(ambient.red + spot.red);
	obj->color.green = (int)(ambient.green + spot.green);
	obj->color.blue = (int)(ambient.blue + spot.blue);
	clamp_colors(&obj->color);
	return (ft_color(obj->color.red, obj->color.green, obj->color.blue, 0xff));
}
