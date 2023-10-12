/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 06:40:21 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/09 12:20:05 by joonasmykka      ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double hit_sphere(const t_sphere *sp, const t_ray *r) {
    t_vector	oc;
    double		a;
    double		b;
    double		c;
    double		discriminant; 

	oc = subtract(r->orig, sp->center);
	a = dotProduct(r->dir, r->dir);
	b = 2.0 * dotProduct(oc, r->dir);
	c = dotProduct(oc, oc) - sp->radius * sp->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return -1;
	else{
		if ((-b - sqrt(discriminant) ) / (2.0 * a) > 0)
			return (-b - sqrt(discriminant) ) / (2.0 * a);
	}
	return -1;
}

static void	check_spheres(t_data *data)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_spheres)
	{
		hit = hit_sphere(&data->scene.spheres[idx], &data->scene.ray);
		if (hit >= 0 && hit < data->pix.closest_t)
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

double	hit_plane(const t_plane *plane, const t_ray *ray)
{
	double 	denominator;
	double 	numerator;
	double	hit;
	
	numerator = dotProduct(plane->point, plane->normal) - dotProduct(ray->orig, plane->normal);
	denominator = dotProduct(ray->dir, plane->normal);
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
		}
	}
}

double hit_cap(t_ray r, double radios, t_vector position, t_vector normal, t_data *data)
{
    float depth;
	t_plane cup;
	double aux;
	t_vector dir;
	t_ray ray;
	t_vector normal1;
	t_vector intersection;
	
	normal1 = normal;
	dir = normalize(r.dir); 
	ray.dir =r.dir;
	ray.orig =r.orig;
	cup.normal = normal1;
	cup.point = position;
    depth = hit_plane(&cup, &ray);
	if(depth < 0)
		return (0);
	intersection = vec_multis(ray.dir, depth);
    intersection = vec_add(r.orig, intersection);
	aux = length(subtract(intersection, position));
    if (aux > radios)
		return (0);
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
	h1 = vec_divide(h, l);
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
	data->pix.cap = BODY;
	if(axis_of < 0.0)
	{
		cap = pos;
		normal = normalize(axis);
		normal = vec_multis(normal, -1);
		double au = hit_cap(r, rad, cap, normal, data);
		if(au != 0)
		{
			if(au < depth || depth == 0)
			{
				data->pix.cap = BOTTOM;
				return (au);
			}
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
			{
				data->pix.cap = TOP;
				return (au1);
			}
		}
	}
	// SHOULD NOT BE NEEDED
	// data->pix.is_cap = 0;
	return (depth);
}

static void	check_cylinders(t_data *data)
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

		}
	}
}

void	shoot_ray(t_data *data)
{
	check_spheres(data);
	check_planes(data);
	check_cylinders(data);
}