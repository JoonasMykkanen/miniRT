/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:06:06 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/09 11:38:18 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray ray_create(const t_vector origin, const t_vector direction)
{
    t_ray ray;
	
	ray.orig = origin;
	ray.dir = direction;
    return ray;
}

t_vector normalize(t_vector vector)
{
	t_vector	normalizedVector;
    double		length;

	length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    normalizedVector.x = vector.x / length;
	normalizedVector.y = vector.y / length;
	normalizedVector.z = vector.z / length;
    return (normalizedVector);
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

t_vector ray_at(const t_ray r, double t)
{
	t_vector res;

	res = vec_add(r.orig, vec_multis(r.dir, (float)t));
    return (res);
}