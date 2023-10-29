/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/29 09:41:19 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

t_color	calculate_ambient(t_data *data, t_color *color, int i)
{
	t_ambient	ambient;

	ambient = data->scene[i].ambient;
	color->red = ambient.color.red * ambient.intensity;
	color->green = ambient.color.green * ambient.intensity;
	color->blue = ambient.color.blue * ambient.intensity;
	color->red *= data->obj[i].color.red / 255.0;
	color->green *= data->obj[i].color.green / 255.0;
	color->blue *= data->obj[i].color.blue / 255.0;
	data->pix[i].ambient = ambient.color;
	return (*color);
}

static double	calculate_spot_light(t_data *data, t_vector point, int i, int idx)
{
	t_vector	pos;
	double		d;

	pos = data->scene[i].lights[idx].position;
	data->pix[i].light_dir = normalize(subtract(pos, point));
	if (data->pix[i].obj_type == PLANE)
		data->pix[i].norm = data->scene[i].planes[data->pix[i].obj_idx].normal;
	else
		data->pix[i].norm = normalize(subtract(point, data->obj[i].point));
	d = fmax(0.0, dot_product(data->pix[i].norm, data->pix[i].light_dir));
	return (d);
}

static void	calculate_specular(t_data *data, t_color *specular, t_vector point, int i, int idx)
{
	double		intensity;
	t_color		color;
	double		angle;
	t_light		light;
	t_vector	half;

	light = data->scene[i].lights[idx];
	data->pix[i].light_dir = normalize(subtract(light.position, point));
	data->pix[i].norm = normalize(subtract(data->scene[i].camera.position, point));
	half = vec_add(data->pix[i].light_dir, data->pix[i].norm);
	half = normalize(half);
	if (data->pix[i].obj_type == PLANE)
		data->pix[i].norm = data->scene[i].planes[data->pix[i].obj_idx].normal;
	else
		data->pix[i].norm = normalize(subtract(point, data->obj[i].point));
	angle = fmax(0.0, dot_product(data->pix[i].norm, half));
	intensity = pow(angle, data->obj[i].shine) * data->obj[i].specular;
	color.red = light.brightness * (intensity * 255);
	color.green = light.brightness * (intensity * 255);
	color.blue = light.brightness * (intensity * 255);
	*specular = color_add(*specular, color);
}

t_color	calculate_color(t_data *data, t_obj *obj, t_vector inter, int i)
{
	t_color	specular = {0,0,0};
	t_color	ambient;
	int		idx;
	t_color	spot = {0,0,0};
	double	d;

	idx = -1;
	calculate_ambient(data, &ambient, i);
	while (++idx < data->scene[i].num_lights)
	{
		if (data->pix[i].obj_type == CYLINDER)
		{
			if (data->scene[i].cylinders[obj->idx].fcylinder == 0)
				d = calculate_body(data, inter, &data->scene[i].cylinders[obj->idx], i, idx);
			else
				d = calculate_cap(data, inter, &data->scene[i].cylinders[obj->idx], i, idx);
		}
		else
			d = calculate_spot_light(data, inter, i, idx);
		spotlight_effect(&data->scene[i].lights[idx], obj, &spot, d);
		calculate_specular(data, &specular, inter, i, idx);
	}
	obj->color.red = (int)(ambient.red + spot.red + specular.red);
	obj->color.green = (int)(ambient.green + spot.green + specular.green);
	obj->color.blue = (int)(ambient.blue + spot.blue + specular.blue);
	clamp_colors(&obj->color);
	return (obj->color);
}
