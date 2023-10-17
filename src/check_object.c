/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 09:24:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 10:21:05 by joonasmykka      ###   ########.fr       */
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

			data->pix.obj_center = data->scene.spheres[idx].center;
			data->pix.obj_radius = data->scene.spheres[idx].radius;
			data->pix.obj_color = data->scene.spheres[idx].color;
		}
	}
}

void	check_planes(t_data *data)
{
	double 	numerator;
	double 	denominator;
	double	hit;
	int		idx;
	
	idx = -1;
	while (++idx < data->scene.num_planes)
	{
		hit = hit_plane(&data->scene.planes[idx], &data->scene.ray);
		if(hit > 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = PLANE;

			data->pix.obj_center = data->scene.planes[idx].point;
			data->pix.obj_color = data->scene.planes[idx].color;
			data->pix.obj_axis = data->scene.planes[idx].normal;
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
		hit = hit_cylinder(data->scene.cylinders[idx].axis, data->scene.cylinders[idx].center, data->scene.cylinders[idx].diameter, data->scene.ray, data->scene.cylinders[idx].height, data);
		if (hit != 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = CYLINDER;

			data->pix.obj_radius = data->scene.cylinders[idx].diameter / 2;
			data->pix.obj_center = data->scene.cylinders[idx].center;
			data->pix.obj_color = data->scene.cylinders[idx].color;
			data->pix.obj_axis = data->scene.cylinders[idx].axis;
		}
	}
}

void	shoot_ray(t_data *data)
{
	check_spheres(data);
	check_planes(data);
	check_cylinders(data);
}