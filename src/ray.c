/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:06:06 by jmykkane          #+#    #+#             */
/*   Updated: 2023/09/26 12:49:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray ray_create(const t_vector origin, const t_vector direction) {
    t_ray r = {origin, direction};
	
    return r;
}

t_vector normalize(t_vector vector)
{
    double length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	
    t_vector normalizedVector = {
        vector.x / length,
        vector.y / length,
        vector.z / length
    };
    return normalizedVector;
}

void	update_ray(t_data *data, int x, int y, t_vector *ray_d) {
	data->scene.camera.help = vec_multis(data->scene.camera.pixu, (float)x);
	data->scene.camera.help1 = vec_multis(data->scene.camera.pixv, (float)y);
	data->scene.camera.center = vec_add(data->scene.camera.help, data->scene.camera.help1);
	data->scene.camera.center = vec_add(data->scene.camera.center, data->scene.camera.pixel);
	*ray_d = subtract(data->scene.camera.center, data->scene.camera.position);
	data->scene.ray = ray_create(data->scene.camera.position, *ray_d);
}

int is_in_shadow(t_vector surface_point, t_vector light_source_position, t_data *data, int self)
{
    // Create a shadow ray from the surface point to the light source
    t_ray shadow_ray = create_shadow_ray(surface_point, light_source_position);
	float t = 0;
    for (int i = 0; i < data->scene.num_spheres; i++) {
		if (i == self)
			continue ;
		t = hit_sphere(data->scene.spheres[i].center, data->scene.spheres[i].radius, shadow_ray);
        if (t > 0) {
            return 1;
        }
    }
    return 0;
}

double hit_sphere(const t_vector center, double radius, const t_ray r) {
    t_vector oc = subtract(r.orig, center);
    double a = dotProduct(r.dir, r.dir);
    double b = 2.0 * dotProduct(oc, r.dir);
    double c = dotProduct(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
	if(discriminant < 0)
		return -1;
	else
		return (-b - sqrt(discriminant) ) / (2.0 * a);
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

t_vector ray_at(const t_ray r, double t) {
	t_vector help;

	help = vec_multis(r.dir, (float)t);
    return vec_add(r.orig, help);
}