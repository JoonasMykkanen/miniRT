/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:31 by djames            #+#    #+#             */
/*   Updated: 2023/10/24 16:44:24 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	draw_plane(t_data *data)
{
	t_color		*color;
	t_vector	inter;

	color = &data->pix.cache_color;
	inter = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(inter, data->scene.light.position, data, data->obj.idx))
	{
		*color = calculate_color(data, &data->obj, inter);
		data->pix.self = data->obj.idx;
		check_reflections(data, inter, data->pix.cache_color);
		data->pix.color = ft_color(color->red, color->green, color->blue, 0xff);
	}
}

static void	draw_cylinder(t_data *data)
{
	t_color		*color;
	t_vector	inter;

	color = &data->pix.cache_color;
	inter = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(inter, data->scene.light.position, data, data->obj.idx))
	{
		*color = calculate_color(data, &data->obj, inter);
		data->pix.self = data->obj.idx;
		check_reflections(data, inter, data->pix.cache_color);
		data->pix.color = ft_color(color->red, color->green, color->blue, 0xff);
	}
}

static void	draw_sphere(t_data *data)
{
	t_color		*color;
	t_vector	inter;

	color = &data->pix.cache_color;
	inter = ray_at(data->scene.ray, data->pix.closest_t);
	if (!is_in_shadow(inter, data->scene.light.position, data, data->obj.idx))
	{
		*color = calculate_color(data, &data->obj, inter);
		data->pix.self = data->obj.idx;
		check_reflections(data, inter, data->pix.cache_color);
		data->pix.color = ft_color(color->red, color->green, color->blue, 0xff);
	}
}

int	render_pixel(t_data *data, int x, int y)
{
	reset_pix(data);
	update_ray(data, x, y);
	shoot_ray(data, &data->scene.ray);
	data->pix.self = -1;
	if (data->obj.type == PLANE)
		draw_plane(data);
	else if (data->obj.type == SPHERE)
		draw_sphere(data);
	else if (data->obj.type == CYLINDER)
		draw_cylinder(data);
	return (data->pix.color);
}
