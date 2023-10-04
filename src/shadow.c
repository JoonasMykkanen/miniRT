/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:37:46 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/04 10:23:33 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Create a shadow ray from the surface point to the light source
int is_in_shadow(t_vector surface_point, t_vector light_source_position, t_data *data, int self)
{
    t_ray	shadow_ray;
	double	d;
	float	t;
	
	t = 0;
	shadow_ray = create_shadow_ray(surface_point, light_source_position);
    for (int i = 0; i < data->scene.num_spheres; i++) {
		if (i == self && data->pix.obj_type == SPHERE)
			continue ;
		t = hit_sphere(data->scene.spheres[i].center, data->scene.spheres[i].radius, shadow_ray);
        if (t > 0) {
            return 1;
        }
    }
	// for (int i = 0; i < data->scene.num_planes; i++) {
	// 	if (i == self  && data->pix.obj_type == PLANE)
	// 		continue ;
	// 	t = hit_plane(data->scene.planes[i], shadow_ray);
	// 	if (t > 0) {
	// 		return 1;
	// 	}
	// }
    return 0;
}

t_ray 		create_shadow_ray(t_vector surface_point, t_vector light_pos)
{
    t_ray	shadow_ray;
	float	length;

    shadow_ray.dir.x = light_pos.x - surface_point.x;
    shadow_ray.dir.y = light_pos.y - surface_point.y;
    shadow_ray.dir.z = light_pos.z - surface_point.z;
    length = dotProduct(shadow_ray.dir, shadow_ray.dir);
	length = sqrtf(length);
    shadow_ray.dir.x /= length;
    shadow_ray.dir.y /= length;
    shadow_ray.dir.z /= length;
    shadow_ray.orig = surface_point;

    return shadow_ray;
}