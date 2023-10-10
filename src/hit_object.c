/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 06:40:21 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/10 12:22:33 by djames           ###   ########.fr       */
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
		if(hit != -1 && hit < data->pix.closest_t)
		{
			// if (hit > 0)
			// {
				data->pix.obj_idx = idx;
				data->pix.closest_t = hit;
				data->pix.obj_type = SPHERE;
			// }else
			// 	data->pix.closest_t = hit;
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
//---------


double hit_cap(t_ray r, double radios, t_vector position, t_vector normal, t_data *data)
{
    float depth;
	t_plane cup;
	double aux;
	t_vector dir;
	t_ray ray;
	t_vector normal1;
	//printf("esto es en x:%f, esto es en y:%f, esto es en z:%f \n",position.x, position.y, position.z);
	
	normal1 = normal;
	dir = normalize(r.dir); 
	ray.dir =r.dir;
	ray.orig =r.orig;
	cup.normal = normal1;
	cup.point = position;
    depth = hit_plane(cup, ray);
	if(depth < 0)
		return (0);
    t_vector intersection;
	intersection = vec_multis(ray.dir, depth);
    intersection = vec_add(r.orig, intersection);
	aux = length(subtract(intersection, position));
    if(aux > (radios))
		return (0);
	data->pix.is_cap = 1;
	return (depth);
}


double hit_cylinder2(const t_vector axis, const t_vector C, double r, const t_ray L, double he) {
    t_vector h; 
	double l;
	t_vector h1;
    double a;
	
    h = normalize(axis);
	h = vec_multis(h, he);
	h = vec_add(h, C);
	h = subtract(h,C);
	l =  length(h);
	h1 = vec_divide(h, l);// cahnging h to h1
    t_vector w;
    w = subtract((L.orig), C);
    t_vector v;
    v = normalize(L.dir);
    a = dotProduct(v, v) - (dotProduct(v, h1) * dotProduct(v, h1));
    double b;
    b = 2.0 * ((dotProduct(v,w)) - ((dotProduct(v,h1)) * (dotProduct(w,h1))));
    double c;
    c  = dotProduct(w,w) - (dotProduct(w,h1) * dotProduct(w,h1)) - r * r;
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {  
    	double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    	double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    	t_vector sol;
    	double projection;
    	sol = vec_multis(v, t1);
    	sol = vec_add((L.orig), sol);
    	sol = subtract(sol, C);
    	projection = dotProduct(sol, h1);	
    	t_vector sol2;
    	double projection2;
    	sol2 = vec_multis(v, t2);
   		sol2 = vec_add((L.orig), sol2);
    	sol2 = subtract(sol2, C);
    	projection2 = dotProduct(sol2, h1);
    	double ho = dotProduct(h1, h1);
    	if (projection >= 0 && projection <= sqrt(h.x * h.x + h.y * h.y + h.z * h.z) && t1 >= 0)
        	return t1;
    // if (projection2 >= 0 && projection2 <= sqrt(h.x * h.x + h.y * h.y + h.z * h.z) && t2 >= 0)
    //     return t2;
     }
    return (0.0);
}

double hit_cylinder(const t_vector axis, const t_vector pos, double rad, const t_ray r, double h, t_data *data)
{
	double depth;
	double axis_of;
	t_vector hit;
	t_vector cap;
	t_vector normal;
	depth = hit_cylinder2(axis, pos, rad, r, h);
	hit = normalize(r.dir);
	hit = vec_multis(hit, depth);
	hit = vec_add(r.orig, hit);
	hit = subtract(hit, pos);
	axis_of = dotProduct(hit, axis);
	data->pix.is_cap = 0;
	if(axis_of < 0.0)
	{
		cap = pos;
		normal = normalize(axis);
		normal = vec_multis(normal, -1);
		double au =hit_cap(r, rad, cap, normal, data);
		if(au != 0)
		{	if(au < depth || depth == 0)
				return (au);
		}
	}
	if(axis_of > h)
	{
		normal = normalize(axis);
		cap= vec_multis(normal, h);
		cap = vec_add(cap, pos);
		double au1 =hit_cap(r, rad, cap, normal, data);
		if(au1 != 0)
		{
			if(au1 < depth || depth == 0)
				return (au1);
		}
	}
	data->pix.is_cap = 0;
	return (depth);
}

// TODO --> add cylinder hit logic when cylinders are drawing
static void	check_cylinder(t_data *data)
{
	double	hit;
	double	t;

	for (int idx = 0; idx < data->scene.num_cylinders; idx++) {
		hit = hit_cylinder(data->scene.cylinders[idx].axis, data->scene.cylinders[idx].center, data->scene.cylinders[idx].diameter, data->scene.ray, data->scene.cylinders[idx].height, data);
		if(hit != 0 && hit < data->pix.closest_t)
		{
			// if (hit > 0)
			// {
				data->pix.obj_idx = idx;
				data->pix.closest_t = hit;
				data->pix.obj_type = CYLINDER;
		// 	}else
		// 		data->pix.closest_t = hit;//(hit < t) && (hit > 0))
		// {
		// 	data->pix.obj_idx = idx;
		// 	data->pix.closest_t = hit;
		// 	data->pix.obj_type = CYLINDER;
		}
	}
}

// This function will shoot rays and determine what object is closest
void	shoot_ray(t_data *data)
{
	check_spheres(data);
	check_planes(data);
	check_cylinder(data);
	// check_cylinders(data);
}