/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:35:43 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/25 10:51:22 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	reflection_color(t_data *d, t_color surface, t_color reflect)
{
	double	kr;
	t_color	final;

	kr = d->obj.reflection;
	final.red = (1.0 - kr) * surface.red + kr * reflect.red;
	final.green = (1.0 - kr) * surface.green + kr * reflect.green;
	final.blue = (1.0 - kr) * surface.blue + kr * reflect.blue;
	d->pix.cache_color = final;
}

static t_ray	create_reflection_ray(t_data *data, t_vector inter)
{
	t_ray		reflection_ray;
	double		dot;

	dot = 2 * (dot_product(data->pix.norm, data->scene.ray.dir));
	reflection_ray.dir = vec_multis(data->pix.norm, dot);
	reflection_ray.dir = subtract(data->scene.ray.dir, reflection_ray.dir);
	reflection_ray.dir = normalize(reflection_ray.dir);
	reflection_ray.orig = vec_add(inter, vec_multis(data->pix.norm, EPSILON));
	return (reflection_ray);
}

void	check_reflections(t_data *data, t_vector inter, t_color surface)
{
	t_ray	reflection_ray;
	t_color	color;

	data->pix.closest_t = FLT_MAX;
	data->pix.reflection_found = false;
	reflection_ray = create_reflection_ray(data, inter);
	shoot_ray(data, &reflection_ray);
	data->scene.ray = reflection_ray;
	if (data->pix.reflection_found == true)
	{
		inter = ray_at(reflection_ray, data->pix.closest_t);
		color = calculate_color(data, &data->obj, inter);
		reflection_color(data, surface, color);
	}
}
