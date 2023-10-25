/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:22 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 11:23:07 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

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
	t_camera	*cam;

	cam = &data->scene.camera;
	cam->help = vec_multis(cam->pixu, (float)x);
	cam->help1 = vec_multis(cam->pixv, (float)y);
	cam->center = vec_add(cam->help, cam->help1);
	cam->center = vec_add(cam->center, data->scene.camera.pixel);
	data->scene.ray.dir = subtract(cam->center, cam->position);
	data->scene.ray = ray_create(cam->position, data->scene.ray.dir);
}

t_vector	ray_at(const t_ray r, double t)
{
	t_vector	res;

	res = vec_add(r.orig, vec_multis(r.dir, (float)t));
	return (res);
}
