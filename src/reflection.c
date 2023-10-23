/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 08:35:43 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/23 10:32:36 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calculate_reflection_color(t_data *data, t_color surface, t_color reflect)
{
	double	kr = data->obj.reflection;
	t_color final;
	
	final.red = (1.0 - kr) * surface.red + kr * reflect.red;
	final.green = (1.0 - kr) * surface.green + kr * reflect.green;
	final.blue = (1.0 - kr) * surface.blue + kr * reflect.blue;
	data->pix.cache_color = final;
}

static t_ray	create_reflection_ray(t_data *data, t_vector inter)
{
	double		epsilon = 0.001;
	t_ray		reflection_ray;
	double		dot;
	
	dot = 2 * (dot_product(data->pix.norm, data->scene.ray.dir));
	reflection_ray.dir = vec_multis(data->pix.norm, dot);
	reflection_ray.dir = subtract(data->scene.ray.dir, reflection_ray.dir);
	reflection_ray.dir = normalize(reflection_ray.dir);
	reflection_ray.orig = vec_add(inter, vec_multis(data->pix.norm, epsilon));

	return (reflection_ray);
}

void	check_reflections(t_data *data, t_vector inter, t_color surface)
{
	t_color	reflection_color;
	t_ray	reflection_ray;
	
	data->pix.closest_t = FLT_MAX;
	data->pix.reflection_found = false;
	reflection_ray = create_reflection_ray(data, inter);
	shoot_ray(data, &reflection_ray);
	if (data->pix.reflection_found == true)
	{
		inter = vec_add(vec_multis(reflection_ray.dir, data->pix.closest_t), reflection_ray.orig);
		reflection_color = calculate_color(data, &data->obj, inter);
		calculate_reflection_color(data, surface, reflection_color);
	}
}
