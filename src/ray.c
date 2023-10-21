/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/21 07:19:11 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_create(const t_vector origin, const t_vector direction)
{
	t_ray	ray;

	ray.orig = origin;
	ray.dir = normalize(direction);
	return (ray);
}

t_vector	normalize(t_vector v)
{
	t_vector	normalized_vector;
	double		length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalized_vector.x = v.x / length;
	normalized_vector.y = v.y / length;
	normalized_vector.z = v.z / length;
	return (normalized_vector);
}

void	update_ray(t_data *data, int x, int y)
{
	data->scene.camera.help = vec_multis(data->scene.camera.pixu, (float)x);
	data->scene.camera.help1 = vec_multis(data->scene.camera.pixv, (float)y);
	data->scene.camera.center = vec_add(data->scene.camera.help, data->scene.camera.help1);
	data->scene.camera.center = vec_add(data->scene.camera.center, data->scene.camera.pixel);
	data->scene.ray.dir = subtract(data->scene.camera.center, data->scene.camera.position);
	data->scene.ray = ray_create(data->scene.camera.position, data->scene.ray.dir);
}

t_vector	ray_at(const t_ray r, double t)
{
	t_vector	res;

	res = vec_add(r.orig, vec_multis(r.dir, (float)t));
	return (res);
}
