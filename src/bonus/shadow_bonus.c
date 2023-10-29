/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:37 by djames            #+#    #+#             */
/*   Updated: 2023/10/29 08:05:03 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

static int	sphere_shadow(t_data *data, t_ray shadow_ray, int i)
{
	int		idx;
	double	hit;

	idx = -1;
	hit = 0;
	while (++idx < data->scene[i].num_spheres)
	{
		hit = hit_sphere(&data->scene[i].spheres[idx], &shadow_ray);
		if (hit > 0)
			return (1);
	}
	return (0);
}

static int	cylinder_shadow(t_data *data, t_ray shadow_ray, int i)
{
	int		idx;
	double	hit;

	idx = -1;
	hit = 0;
	while (++idx < data->scene[i].num_cylinders)
	{
		hit = hit_cylinder(&data->scene[i].cylinders[idx], shadow_ray);
		if (hit != 0)
			return (1);
	}
	return (0);
}

static t_ray	create_shadow_ray(t_vector surface_point, t_vector light_pos, t_vector normal)
{
	t_ray   	shadow_ray;
    float   	length;

    shadow_ray.orig.x = surface_point.x + normal.x * EPSILON;
    shadow_ray.orig.y = surface_point.y + normal.y * EPSILON;
    shadow_ray.orig.z = surface_point.z + normal.z * EPSILON;
    shadow_ray.dir.x = light_pos.x - shadow_ray.orig.x;
    shadow_ray.dir.y = light_pos.y - shadow_ray.orig.y;
    shadow_ray.dir.z = light_pos.z - shadow_ray.orig.z;
    length = sqrtf(dot_product(shadow_ray.dir, shadow_ray.dir));
    shadow_ray.dir.x /= length;
    shadow_ray.dir.y /= length;
    shadow_ray.dir.z /= length;

    return (shadow_ray);
}

int	is_in_shadow(t_vector point, t_data *d, int i, t_vector normal)
{
	t_ray		shadow_ray;
	t_color		ambient;
	t_vector	light;
	int			idx;

	idx = -1;
	while (++idx < d->scene[i].num_lights)
	{
		light = d->scene[i].lights[idx].position;
		shadow_ray = create_shadow_ray(point, light, normal);
		if (sphere_shadow(d, shadow_ray, i))
		{
			calculate_ambient(d, &ambient, i);
			d->pix[i].color = ft_color(ambient.red, ambient.green, ambient.blue, 0xff);
			d->scene->in_shadow[idx] = false;
			return (1);
		}
		else if (cylinder_shadow(d, shadow_ray, i))
		{
			calculate_ambient(d, &ambient, i);
			d->pix[i].color = ft_color(ambient.red, ambient.green, ambient.blue, 0xff);
			d->scene->in_shadow[idx] = false;
			return (1);
		}
	}
	d->scene->in_shadow[idx] = true;
	return (0);
}
