/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:28:48 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 13:09:48 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

void	check_spheres(t_data *data, t_ray *ray, int i)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene[i].num_spheres)
	{
		hit = hit_sphere(&data->scene[i].spheres[idx], ray);
		if (hit >= 0 && hit < data->pix[i].closest_t)
		{
			data->pix[i].reflection_found = true;
			data->pix[i].obj_idx = idx;
			data->pix[i].closest_t = hit;
			data->pix[i].obj_type = SPHERE;
			data->obj[i].idx = idx;
			data->obj[i].type = SPHERE;
			data->obj[i].point = data->scene[i].spheres[idx].center;
			data->obj[i].color = data->scene[i].spheres[idx].color;
			data->obj[i].radius = data->scene[i].spheres[idx].radius;
		}
	}
}

// If check is used to disable plane to plane reflections
void	check_planes(t_data *data, t_ray *ray, int i)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene[i].num_planes)
	{
		hit = hit_plane(&data->scene[i].planes[idx], ray);
		if (hit > 0 && hit < data->pix[i].closest_t)
		{
			if (data->obj[i].type != PLANE)
				data->pix[i].reflection_found = true;
			data->pix[i].obj_idx = idx;
			data->pix[i].closest_t = hit;
			data->pix[i].obj_type = PLANE;
			data->obj[i].idx = idx;
			data->obj[i].type = PLANE;
			data->obj[i].axis = data->scene[i].planes[idx].normal;
			data->obj[i].point = data->scene[i].planes[idx].point;
			data->obj[i].color = data->scene[i].planes[idx].color;
			data->obj[i].radius = -1;
		}
	}
}

void	check_cylinders(t_data *data, t_ray *ray, int i)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene[i].num_cylinders)
	{
		hit = hit_cylinder(&data->scene[i].cylinders[idx], *ray);
		if (hit != 0 && hit < data->pix[i].closest_t)
		{
			data->pix[i].reflection_found = true;
			data->pix[i].obj_idx = idx;
			data->pix[i].closest_t = hit;
			data->pix[i].obj_type = CYLINDER;
			data->obj[i].idx = idx;
			data->obj[i].type = CYLINDER;
			data->obj[i].axis = data->scene[i].cylinders[idx].axis;
			data->obj[i].point = data->scene[i].cylinders[idx].center;
			data->obj[i].color = data->scene[i].cylinders[idx].color;
			data->obj[i].radius = data->scene[i].cylinders[idx].diameter / 2;
		}
	}
}

static void	init_obj(t_obj *obj, t_data *data, int i)
{
	if (data->pix[i].obj_type == PLANE)
	{
		obj->shine = PLANE_SHINE;
		obj->specular = PLANE_SPECULAR;
		obj->reflection = PLANE_REFLECTION;
	}
	else if (data->pix[i].obj_type == SPHERE)
	{
		obj->shine = SPHERE_SHINE;
		obj->specular = SPHERE_SPECULAR;
		obj->reflection = SPHERE_REFLECTION;
	}
	else if (data->pix[i].obj_type == CYLINDER)
	{
		obj->shine = CYLINDER_SHINE;
		obj->specular = CYLINDER_SPECULAR;
		obj->reflection = CYLINDER_REFLECTION;
	}
}

void	shoot_ray(t_data *data, t_ray *ray, int i)
{
	init_obj(&data->obj[i], data, i);
	check_spheres(data, ray, i);
	check_planes(data, ray, i);
	check_cylinders(data, ray, i);
}
