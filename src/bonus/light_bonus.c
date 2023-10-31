/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/31 12:06:36 by jmykkane         ###   ########.fr       */
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

static double	calculate_spot_light(t_data *data, t_vector point, int i,
		int idx)
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

static void	calculate_specular(
		t_data *data, t_vector point, int i, int idx)
{
	double		intensity;
	t_color		color;
	double		angle;
	t_light		light;
	t_vector	half;

	light = data->scene[i].lights[idx];
	data->pix[i].light_dir = normalize(subtract(light.position, point));
	data->pix[i].norm = normalize(subtract(data->scene[i].camera.position,
				point));
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
	data->pix[i].specular = color_add(data->pix[i].specular, color);
}

void	init_values(t_data *data, int *idx, int i)
{
	data->pix[i].specular.blue = 0;
	data->pix[i].specular.green = 0;
	data->pix[i].specular.red = 0;
	data->pix[i].spot.blue = 0;
	data->pix[i].spot.green = 0;
	data->pix[i].spot.red = 0;
	*idx = -1;
}

t_color	calculate_color(t_data *data, t_obj *obj, t_vector inter, int i)
{
	int		idx;
	double	d;

	init_values(data, &idx, i);
	calculate_ambient(data, &data->pix[i].ambient1, i);
	while (++idx < data->scene[i].num_lights)
	{
		if (data->scene[i].in_shadow[idx] == true)
			continue ;
		if (data->pix[i].obj_type == CYLINDER)
			d = cylinder_light(data, inter, i, idx);
		else
			d = calculate_spot_light(data, inter, i, idx);
		spotlight_effect(&data->scene[i].lights[idx],
			obj, &data->pix[i].spot, d);
		calculate_specular(data, inter, i, idx);
	}
	obj->color.red = (int)(data->pix[i].ambient1.red + data->pix[i].spot.red
			+ data->pix[i].specular.red);
	obj->color.green = (int)(data->pix[i].ambient1.green
			+ data->pix[i].spot.green + data->pix[i].specular.green);
	obj->color.blue = (int)(data->pix[i].ambient1.blue + data->pix[i].spot.blue
			+ data->pix[i].specular.blue);
	clamp_colors(&obj->color);
	return (obj->color);
}
