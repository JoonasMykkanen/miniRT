/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:35:43 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/26 13:13:09 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

static void	reflection_color(t_data *d, t_color surface, t_color reflect, int i)
{
	double	kr;
	t_color	final;

	kr = d->obj[i].reflection;
	final.red = (1.0 - kr) * surface.red + kr * reflect.red;
	final.green = (1.0 - kr) * surface.green + kr * reflect.green;
	final.blue = (1.0 - kr) * surface.blue + kr * reflect.blue;
	d->pix[i].cache_color = final;
}

static t_ray	create_reflection_ray(t_data *data, t_vector inter, int i)
{
	t_ray		reflection_ray;
	double		dot;

	dot = 2 * (dot_product(data->pix[i].norm, data->scene[i].ray.dir));
	reflection_ray.dir = vec_multis(data->pix[i].norm, dot);
	reflection_ray.dir = subtract(data->scene[i].ray.dir, reflection_ray.dir);
	reflection_ray.dir = normalize(reflection_ray.dir);
	reflection_ray.orig = vec_add(inter, vec_multis(data->pix[i].norm, EPSILON));
	return (reflection_ray);
}

void	check_reflections(t_data *data, t_vector inter, t_color surface, int i)
{
	t_ray	reflection_ray;
	t_color	color;

	data->pix[i].closest_t = FLT_MAX;
	data->pix[i].reflection_found = false;
	reflection_ray = create_reflection_ray(data, inter, i);
	shoot_ray(data, &reflection_ray, i);
	data->scene[i].ray = reflection_ray;
	if (data->pix[i].reflection_found == true)
	{
		inter = ray_at(reflection_ray, data->pix[i].closest_t);
		color = calculate_color(data, &data->obj[i], inter, i);
		reflection_color(data, surface, color, i);
	}
}
