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
	else
		return (-b - sqrt(discriminant) ) / (2.0 * a);
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
			data->pix.obj_idx = idx;
			data->pix.closest_t = hit;
			data->pix.obj_type = SPHERE;
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

double hit_cap(t_ray ray, double radios, t_vector position, t_vector normal, t_data *data)
{
    t_vector	intersection;
	t_plane		cap;
	double 		aux;
    float		t;

	cap.normal = normal;
	cap.point = position;
    t = hit_plane(&cap, &ray);
	if (t < 0)
		return (0);
	intersection = ray_at(ray, t);
	aux = length(subtract(intersection, position));
    if (aux > radios)
		return (0);
	return (t);
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
    	if (projection >= 0 && projection <= sqrt(h1.x * h1.x + h1.y * h1.y + h1.z * h1.z) && t1 >= 0)
        	return t1;
    }
    return (0.0);
}

double hit_cylinder(t_data *data, t_cylinder *cyl, t_ray *ray)
{
	double depth;
	double axis_of;
	t_vector hit;
	t_vector cap;
	t_vector normal;
	
	depth = hit_cylinder2(cyl->axis, cyl->center, cyl->diameter, *ray, cyl->height);
	hit = normalize(ray->dir); // TESTING WITHOUT
	hit = vec_multis(hit, depth);
	hit = vec_add(ray->orig, hit);
	hit = subtract(hit, cyl->center);
	axis_of = dotProduct(hit, cyl->axis);
	if (axis_of < 0.0)
	{
		cap = cyl->center;
		normal = normalize(cyl->axis); // TESTING WITHOUT
		normal = vec_multis(normal, -1); // WHAT is -1 
		double au = hit_cap(*ray, cyl->diameter, cap, normal, data);
		if (au != 0)
		{	if (au < depth || depth == 0)
				depth = au;
		}
	}
	else if (axis_of > cyl->height)
	{
		normal = normalize(cyl->axis);
		cap= vec_multis(normal, cyl->height);
		cap = vec_add(cap, cyl->center);
		double au1 =hit_cap(*ray, cyl->diameter, cap, normal, data);
		if (au1 != 0)
		{
			if (au1 < depth || depth == 0)
				depth = au1;
		}
	}
	return (depth);
}

static void	check_cylinders(t_data *data)
{
	double	hit;
	int		idx;

	idx = -1;
	while (++idx < data->scene.num_cylinders)
	{
		hit = hit_cylinder(data, &data->scene.cylinders[idx], &data->scene.ray);
		if (hit > 0 && hit < data->pix.closest_t)
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