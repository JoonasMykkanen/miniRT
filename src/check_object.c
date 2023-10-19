/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:28:48 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:49:44 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_spheres(t_data *data)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_spheres)
	{
		hit = hit_sphere(&data->scene.spheres[idx], &data->scene.ray);
		if (hit >= 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = SPHERE;
			data->obj.idx = idx;
			data->obj.type = SPHERE;
			data->obj.point = data->scene.spheres[idx].center;
			data->obj.color = data->scene.spheres[idx].color;
			data->obj.radius = data->scene.spheres[idx].radius;
		}
	}
}

void	check_planes(t_data *data)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_planes)
	{
		hit = hit_plane(&data->scene.planes[idx], &data->scene.ray);
		if (hit > 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = PLANE;
			data->obj.idx = idx;
			data->obj.type = PLANE;
			data->obj.axis = data->scene.planes[idx].normal;
			data->obj.point = data->scene.planes[idx].point;
			data->obj.color = data->scene.planes[idx].color;
			data->obj.radius = -1;
		}
	}
}

void	check_cylinders(t_data *data)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_cylinders)
	{
		hit = hit_cylinder(&data->scene.cylinders[idx], data->scene.ray);
		if (hit != 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = CYLINDER;
			data->obj.idx = idx;
			data->obj.type = CYLINDER;
			data->obj.axis = data->scene.cylinders[idx].axis;
			data->obj.point = data->scene.cylinders[idx].center;
			data->obj.color = data->scene.cylinders[idx].color;
			data->obj.radius = data->scene.cylinders[idx].diameter / 2;
		}
	}
}

void	shoot_ray(t_data *data)
{
	check_spheres(data);
	check_planes(data);
	check_cylinders(data);
}
