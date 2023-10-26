/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:31 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 13:14:35 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

static void	draw_plane(t_data *data, int i)
{
	t_color		*color;
	t_vector	inter;

	color = &data->pix[i].cache_color;
	inter = ray_at(data->scene[i].ray, data->pix[i].closest_t);
	if (!is_in_shadow(inter, data, i)) 
	{
		*color = calculate_color(data, &data->obj[i], inter, i);
		data->pix[i].self = data->obj[i].idx;
		check_reflections(data, inter, data->pix[i].cache_color, i);
		data->pix[i].color = ft_color(color->red, color->green, color->blue, 0xff);
	}
}

static void	draw_cylinder(t_data *data, int i)
{
	t_color		*color;
	t_vector	inter;

	color = &data->pix[i].cache_color;
	inter = ray_at(data->scene[i].ray, data->pix[i].closest_t);
	if (!is_in_shadow(inter, data, i)) 
	{
		*color = calculate_color(data, &data->obj[i], inter, i);
		data->pix[i].self = data->obj[i].idx;
		check_reflections(data, inter, data->pix[i].cache_color, i);
		data->pix[i].color = ft_color(color->red, color->green, color->blue, 0xff);
	}
}

static void	draw_sphere(t_data *data, int i)
{
	t_color		*color;
	t_vector	inter;

	color = &data->pix[i].cache_color;
	inter = ray_at(data->scene[i].ray, data->pix[i].closest_t);
	if (!is_in_shadow(inter, data, i)) 
	{
		*color = calculate_color(data, &data->obj[i], inter, i);
		data->pix[i].self = data->obj[i].idx;
		check_reflections(data, inter, data->pix[i].cache_color, i);
		data->pix[i].color = ft_color(color->red, color->green, color->blue, 0xff);
	}
}

int	render_pixel(t_data *data, int x, int y, int i)
{
	reset_pix(data, i);
	update_ray(data, x, y, i);
	shoot_ray(data, &data->scene[i].ray, i);
	data->pix[i].self = -1;
	if (data->obj[i].type == PLANE)
		draw_plane(data, i);
	else if (data->obj[i].type == SPHERE)
		draw_sphere(data, i);
	else if (data->obj[i].type == CYLINDER)
		draw_cylinder(data, i);
	return (data->pix[i].color);
}
