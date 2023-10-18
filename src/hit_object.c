/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 06:40:21 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 11:59:35 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(const t_sphere *sp, const t_ray *r) {
    double		discriminant; 
    t_vector	oc;
    double		a;
    double		b;
    double		c;

	oc = subtract(r->orig, sp->center);
	a = dot_product(r->dir, r->dir);
	b = 2.0 * dot_product(oc, r->dir);
	c = dot_product(oc, oc) - sp->radius * sp->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return -1;
	return (-b - sqrt(discriminant) ) / (2.0 * a);
}



double	hit_plane(const t_plane *plane, const t_ray *ray)
{
	double 	denominator;
	double 	numerator;
	double	hit;
	
	numerator = dot_product(plane->point, plane->normal) - dot_product(ray->orig, plane->normal);
	denominator = dot_product(ray->dir, plane->normal);
	if (denominator == 0.0)
		return (-1);
	hit = numerator / denominator;
	return (hit);
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
    a = dot_product(v, v) - (dot_product(v, h1) * dot_product(v, h1));
    double b;
    b = 2.0 * ((dot_product(v,w)) - ((dot_product(v,h1)) * (dot_product(w,h1))));
    double c;
    c  = dot_product(w,w) - (dot_product(w,h1) * dot_product(w,h1)) - r * r;
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
    	projection = dot_product(sol, h1);	
    	t_vector sol2;
    	double projection2;
    	sol2 = vec_multis(v, t2);
   		sol2 = vec_add((L.orig), sol2);
    	sol2 = subtract(sol2, C);
    	projection2 = dot_product(sol2, h1);
    	double ho = dot_product(h1, h1);
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
	axis_of = dot_product(hit, axis);
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
	return (depth);
}

