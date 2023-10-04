/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 06:40:21 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/04 16:36:03 by djames           ###   ########.fr       */
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

double hit_cap(t_ray r, double radios, t_vector position, t_vector normal)
{
    float depth;
	t_plane cup;
	double aux;
	t_vector dir;
	t_ray ray;
	
	normal = normalize(normal);
	dir = normalize(r.dir);
	ray.dir =dir;
	ray.orig =r.orig;
	cup.normal = normal;
	cup.point = position;
    depth = hit_plane(cup, ray);
    t_vector intersection;
	intersection = vec_multis(r.dir, depth);
    intersection = vec_add(r.orig, intersection);
	aux = length(subtract(intersection, position));
    if(aux > radios)
		return (0);
	return (depth);
}


double hit_cylinder2(const t_vector axis, const t_vector C, double r, const t_ray L) {
    t_vector h = axis; //vec_subtract(&axis, &C);
    //t_vector h = {H.x - C.x, H.y - C.y, H.z - C.z};
    //t_vector w = {L.orig.x - C.x, L.orig.y - C.y, L.orig.z - C.z};
    h = normalize(h);
    t_vector w;
    w = subtract((L.orig), C);
    //t_vector v = {L.dir.x, L.dir.y, L.dir.z};
    t_vector v;
    v = normalize(L.dir);

    //double a = v.x * v.x + v.y * v.y - (v.x * h.x + v.y * h.y) * (v.x * h.x + v.y * h.y);
    double a;
    a = 1.0 - (dotProduct(v, h) * dotProduct(v, h));
   //double b = 2.0 * (w.x * v.x + w.y * v.y - (w.x * h.x + w.y * h.y) * (v.x * h.x + v.y * h.y));
    double b;
    b = 2.0 * ((dotProduct(v,w)) - ((dotProduct(v,h)) * (dotProduct(w,h))));
    //double c = w.x * w.x + w.y * w.y - (w.x * h.x + w.y * h.y) * (w.x * h.x + w.y * h.y) - r * r;
    double c;
    c  = dotProduct(w,w) - (dotProduct(w,h) * dotProduct(w,h)) - r * r;

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {   //return -1.0;  // No intersection

    // Calculate the two possible values of t
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    // Calculate the projection of the intersection point onto the cylinder axis
    //double projection = (w.x + t1 * v.x - C.x) * h.x + (w.y + t1 * v.y - C.y) * h.y + (w.z + t1 * v.z - C.z) * h.z;
    t_vector sol;
    double projection;
    sol = vec_multis(v, t1);
    sol = vec_add((L.orig), sol);
    sol = subtract(sol, C);
    projection = dotProduct(sol, h);
    // if (projection <= 0)
    //     return t1;
    t_vector sol2;
    double projection2;
    sol2 = vec_multis(v, t2);
    sol2 = vec_add((L.orig), sol2);
    sol2 = subtract(sol2, C);
    projection2 = dotProduct(sol2, h);
    // if (projection2 < 0 && t2 >= 0)
    //     return t2;
    double ho = dotProduct(h, h);
    if (projection >= 0 && projection <= ho)
        return t1;
    if (projection2 >= 0 && projection2 <= ho)
         return t2;
    // if(projection2 >  ho)
    //     return t2;
    // }
    //Check the intersection conditions
    //  if (projection >= 0 && projection <= sqrt(h.x * h.x + h.y * h.y + h.z * h.z) && t1 >= 0)
    //      return t1;

    // if (projection2 >= 0 && projection2 <= sqrt(h.x * h.x + h.y * h.y + h.z * h.z) && t2 >= 0)
    //     return t2;
    // // // //if ()
    }
    // double circleup = hit_circle(C, r, L) ;
    // if (circleup >= 0)
    //     return circleup;
    // double circledown = hit_circle(H, r, L) ;
    // if (circledown >= 0)
    //     return circledown;

    return 0.0;  // No valid intersection
}

double hit_cylinder(const t_vector axis, const t_vector pos, double rad, const t_ray r, double h)
{
	double depth;
	double axis_of;
	t_vector hit;
	t_vector cap;
	t_vector normal;
	depth = hit_cylinder2(axis, pos, rad, r);
	// if (depth != 0 )
	// 	return (depth);
	//hit = normalize(r.dir);
	hit = vec_multis(hit, depth);
	hit = vec_add(r.orig, hit);
	axis_of = dotProduct(hit, axis);
	if(axis_of < 0.0)
	{
		cap = pos;
		normal = normalize(axis);
		normal = vec_multis(normal, -1);
		return (hit_cap(r, rad, cap, normal));
	}
	if(axis_of < h)
	{
		cap= vec_multis(axis, h);
		cap = vec_add(cap, pos);
		normal = axis;
		return (hit_cap(r, rad, cap, normal)); 
	}
	return (depth);
	
	// intersection = vec_multis(r.dir, depth);
    // intersection = vec_add(r.orig, r.dir);
}
// TODO --> add cylinder hit logic when cylinders are drawing
static void	check_cylinder(t_data *data)
{
	double	hit;
	double	t;

	for (int idx = 0; idx < data->scene.num_spheres; idx++) {
		hit = hit_cylinder(data->scene.cylinders[idx].axis, data->scene.cylinders[idx].center, data->scene.cylinders[idx].diameter, data->scene.ray, data->scene.cylinders[idx].height);
		if(hit != 0)//(hit < t) && (hit > 0))
		{
			data->pix.obj_idx = idx;
			data->pix.closest_t = t;
			data->pix.obj_type = CYLINDER;
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