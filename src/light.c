/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/29 10:43:54 by jmykkane         ###   ########.fr       */
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

t_color	calculate_color(t_data *data, t_obj *obj, t_vector inter)
{
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
	obj->color.red = (int)(ambient.red + spot.red);
	obj->color.green = (int)(ambient.green + spot.green);
	obj->color.blue = (int)(ambient.blue + spot.blue);
	clamp_colors(&obj->color);
	return (obj->color);
}
