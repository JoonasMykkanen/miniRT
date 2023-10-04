/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 06:40:21 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/30 08:41:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static void	check_spheres(t_data *data)
{
	double	hit;

	for (int idx = 0; idx < data->scene.num_spheres; idx++) {
		hit = hit_sphere(data->scene.spheres[idx].center, data->scene.spheres[idx].radius, data->scene.ray);
		if(hit >= 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = SPHERE;
		}
	}
}

double	hit_plane(t_plane plane, t_ray ray)
{
	double 	denominator;
	double 	numerator;
	double	hit;

	numerator = dotProduct(plane.point, plane.normal) - dotProduct(ray.orig, plane.normal);
	denominator = dotProduct(ray.dir, plane.normal);
	if (denominator == 0.0)
		return (-1);
	hit = numerator / denominator;
	return (hit);
}

// double	max = 10;
// double	min = -1 * max;
// double t;

// t = hit_plane(data->scene.planes[0], data->scene.ray);

// if (t > 0) {
// 	t_vector intersection_point = vec_add(vec_multis(data->scene.ray.dir, t), data->scene.ray.orig);
	
// 	if (intersection_point.x > max || intersection_point.x < min || intersection_point.z > max || intersection_point.z < min || intersection_point.y > max || intersection_point.y < min)
// 		return ;
// 	double d = dist(data->scene.ray.orig, intersection_point);
// 	if (d > data->pix.closest_t && data->pix.closest_t != 10)
// 		return ;
// 	data->pix.color = calculate_color(data, data->scene.planes[0].point, data->scene.planes[0].color);
// }
static void	check_planes(t_data *data)
{
	double 	numerator;
	double 	denominator;
	double	hit;
	
	for (int idx = 0; idx < data->scene.num_planes; idx++) {
		hit = hit_plane(data->scene.planes[idx], data->scene.ray);
		if(hit > 0 && hit < data->pix.closest_t)
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = PLANE;
		}
	}
}

// TODO --> add cylinder hit logic when cylinders are drawing
// static void	check_cylinders(t_data *data)
// {
// 	double	hit;
// 	double	t;

// 	for (int idx = 0; idx < data->scene.num_spheres; idx++) {
// 		hit = hit_sphere(data->scene.spheres[idx].center, data->scene.spheres[idx].radius, data->scene.ray);
// 		if((hit < t) && (hit > 0))
// 		{
// 			data->pix.obj_idx = idx;
// 			data->pix.closest_t = t;
// 			data->pix.obj_type = SPHERE;
// 		}
// 	}
// }

// This function will shoot rays and determine what object is closest
void	shoot_ray(t_data *data)
{
	check_spheres(data);
	check_planes(data);
}