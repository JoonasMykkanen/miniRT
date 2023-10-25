/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:28:48 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 11:44:55 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_spheres(t_data *data, t_ray *ray)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_spheres)
	{
		hit = hit_sphere(&data->scene.spheres[idx], ray);
		if (hit >= 0 && hit < data->pix.closest_t)
		{
			data->pix.reflection_found = true;
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

// If check is used to disable plane to plane reflections
void	check_planes(t_data *data, t_ray *ray)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_planes)
	{
		hit = hit_plane(&data->scene.planes[idx], ray);
		if (hit > 0 && hit < data->pix.closest_t)
		{
			if (data->obj.type != PLANE)
				data->pix.reflection_found = true;
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

void	check_cylinders(t_data *data, t_ray *ray)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_cylinders)
	{
		hit = hit_cylinder(&data->scene.cylinders[idx], *ray);
		if (hit != 0 && hit < data->pix.closest_t)
		{
			data->pix.reflection_found = true;
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

void	shoot_ray(t_data *data, t_ray *ray)
{
	check_spheres(data, ray);
	check_planes(data, ray);
	check_cylinders(data, ray);
}
