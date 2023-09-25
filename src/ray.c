/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:06:06 by jmykkane          #+#    #+#             */
/*   Updated: 2023/09/18 11:20:04 by jmykkane         ###   ########.fr       */
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

// TODO -> Make sure what variables needs to be recalculated...
// TODO -> our rays aim at one fixed point that makes moving look weird
// 		   it's always aiming for that one specific location
void	update_ray(t_data *data, int x, int y, t_vector *ray_d) {
	data->scene.camera.help = vec_multis(data->scene.camera.pixu, (float)x);
	data->scene.camera.help1 = vec_multis(data->scene.camera.pixv, (float)y);
	data->scene.camera.center = vec_add(data->scene.camera.help, data->scene.camera.help1);
	data->scene.camera.center = vec_add(data->scene.camera.center, data->scene.camera.pixel);
	*ray_d = subtract(data->scene.camera.center, data->scene.camera.position);
	data->scene.ray = ray_create(data->scene.camera.position, *ray_d);
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