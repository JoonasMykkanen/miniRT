/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:37 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:32:40 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	sphere_shadow(t_data *data, t_ray shadow_ray, int self)
{
	int		idx;
	double	hit;

	idx = -1;
	hit = 0;
	while (++idx < data->scene.num_spheres)
	{
		if (idx == self && data->pix.obj_type == SPHERE)
			continue ;
		hit = hit_sphere(&data->scene.spheres[idx], &shadow_ray);
		if (hit > 0)
			return (1);
	}
	return (0);
}

static int	cylinder_shadow(t_data *data, t_ray shadow_ray, int self)
{
	int		idx;
	double	hit;

	idx = -1;
	hit = 0;
	while (++idx < data->scene.num_cylinders)
	{
		if (idx == self && data->pix.obj_type == CYLINDER)
			continue ;
		hit = hit_cylinder(&data->scene.cylinders[idx], shadow_ray, data);
		if (hit != 0)
			return (1);
	}
	return (0);
}

int	is_in_shadow(t_vector point, t_vector light_pos, t_data *data, int self)
{
	t_ray	shadow_ray;

	shadow_ray = create_shadow_ray(point, light_pos);
	if (sphere_shadow(data, shadow_ray, self))
		return (1);
	if (cylinder_shadow(data, shadow_ray, self))
		return (1);
	return (0);
}

t_ray	create_shadow_ray(t_vector surface_point, t_vector light_pos)
{
	t_ray	shadow_ray;
	float	length;

	shadow_ray.dir.x = light_pos.x - (surface_point.x + 0.001);
	shadow_ray.dir.y = light_pos.y - (surface_point.y + 0.001);
	shadow_ray.dir.z = light_pos.z - (surface_point.z + 0.001);
	length = sqrtf(dot_product(shadow_ray.dir, shadow_ray.dir));
	shadow_ray.dir.x /= length;
	shadow_ray.dir.y /= length;
	shadow_ray.dir.z /= length;
	shadow_ray.orig = surface_point;
	return (shadow_ray);
}
